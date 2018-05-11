//
//  compareLib.cpp
//  Thesis-Evaluation-Tool
//
//  Created by Kyle Mulligan on 5/9/18.
//  Copyright © 2018 Kyle Mulligan. All rights reserved.
//

#include "compareLib.hpp"





//Compare two input lists of images


//function to compare the rectangles
void imageCompareSerial(std::list<Image*> traineeImages, std::list<Image*> expertImages)
{
    std::list<Image*>::const_iterator traineeImagesIterator;
    std::list<Image*>::const_iterator expertImagesIterator;
    
    for ( expertImagesIterator=expertImages.begin(), traineeImagesIterator=traineeImages.begin();
         expertImagesIterator!=expertImages.end() && traineeImagesIterator!=traineeImages.end();
         ++expertImagesIterator, ++traineeImagesIterator)
    {
        rectangleCompareSerial( (*traineeImagesIterator), (*expertImagesIterator));
    }
}

//creates threads to compare images
void imageCompareParallelWrapper(std::vector<Image*> traineeImages, std::vector<Image*> expertImages, int numThreads)
{
    std::vector<std::thread> threadVec;
    
    int threadCount;

    
    
    threadVec.reserve(numThreads);
    
    for (threadCount=0; threadCount < numThreads; ++threadCount)
    {
        threadVec.push_back(std::thread(imageCompareParallel, traineeImages, expertImages, numThreads, threadCount));
        
    }
    
    for ( threadCount=0; threadCount < numThreads; ++threadCount)
    {
        (threadVec.back()).join();
        threadVec.pop_back();
    }
}

//threaded function that compares threads
void imageCompareParallel(std::vector<Image*> traineeImages, std::vector<Image*> expertImages, int numThreads, int threadNumber)
{
    
    
    std::list<Rectangle*> keyRects;
    std::list<Rectangle*> checkRects;
    
    
    
    size_t numImgs =expertImages.size();
    
    size_t blockSize=numImgs/numThreads;
    size_t start=threadNumber*(blockSize);
    size_t end;
    size_t img;
    
    if (threadNumber!=(numThreads-1))
    {
        end=start+blockSize;
    }
    else
    {
        end=numImgs;
    }
    
    for ( img=start ; img<end; img++)
    {
        rectangleCompareSerial( traineeImages[img], expertImages[img]);
    }
        

}


//function to compare the expert rectangles
void rectangleCompareSerial( Image* traineeImage, Image* expertImage)
{
    std::list<Rectangle*> expertRectangles = expertImage->getAllRectangles();
    std::list<Rectangle*>::iterator expertRectanglesIterator;
    
    
    
    for ( expertRectanglesIterator=expertRectangles.begin();
         expertRectanglesIterator!=expertRectangles.end();
         ++expertRectanglesIterator)
    {
        traineeRectangleCompare(traineeImage, (*expertRectanglesIterator));
        expertImage->increaseNumMatches2((*expertRectanglesIterator)->getMatch2score());
    }
    
    
}

//threaded function to compare the rectangles
void rectangleCompareParallel( Image* traineeImage, Image* expertImage)
{
    std::list<Rectangle*> expertRectangles = expertImage->getAllRectangles();
    std::list<Rectangle*>::iterator expertRectanglesIterator;
    
    std::vector<std::thread> threadVec;
    
    
    int numExpertRectangles;
    
    numExpertRectangles=expertImage->getNumRects();
    
    threadVec.reserve(numExpertRectangles);
    
    for ( expertRectanglesIterator=expertRectangles.begin();
         expertRectanglesIterator!=expertRectangles.end();
         ++expertRectanglesIterator)
    {
        
        //for each rectangle in the key list, check against all rectangles in the check rectangles list by creating a new thread per rectangle in the key list.
        
        
        threadVec.push_back(std::thread(traineeRectangleCompare, traineeImage, (*expertRectanglesIterator) ));
    }
    
    
    //join the threads
    while ( !threadVec.empty() )
    {
        (threadVec.back()).join();
        threadVec.pop_back();
    }
    
    for ( expertRectanglesIterator=expertRectangles.begin();
         expertRectanglesIterator!=expertRectangles.end();
         ++expertRectanglesIterator)
    {
        expertImage->increaseNumMatches2((*expertRectanglesIterator)->getMatch2score());
    }
    
}


//function that actually does the comparisons
void traineeRectangleCompare( Image* traineeImage, Rectangle* expertRectangle)
{
    std::list<Rectangle*> traineeRectangles = traineeImage->getAllRectangles();
    std::list<Rectangle*>::iterator traineeRectanglesIterator;
    
    double keyX0;
    double keyX1;
    double keyY0;
    double keyY1;
    double keyArea;
    
    double checkX0;
    double checkX1;
    double checkY0;
    double checkY1;
    double checkArea;
    
    double inX0;
    double inX1;
    double inY0;
    double inY1;
    double inArea;
    
    double rectScore;
    
    for ( traineeRectanglesIterator=traineeRectangles.begin(); traineeRectanglesIterator!=traineeRectangles.end(); ++traineeRectanglesIterator)
    {
        
        //if the tags are not the same, this is not the correct rectangle so continue
        if ( (expertRectangle->getTag()) != ((*traineeRectanglesIterator)->getTag() ))
        {
            continue;
        }
        //if the tags are the same, this may be the correct rectangle.
        else
        {
            //get the corners of the rectangles and the areas
            keyX0 = expertRectangle->getX0();
            keyX1 = expertRectangle->getX1();
            keyY0 = expertRectangle->getY0();
            keyY1 = expertRectangle->getY1();
            keyArea = expertRectangle->getArea();
            
            checkX0 = (*traineeRectanglesIterator)->getX0();
            checkX1 = (*traineeRectanglesIterator)->getX1();
            checkY0 = (*traineeRectanglesIterator)->getY0();
            checkY1 = (*traineeRectanglesIterator)->getY1();
            checkArea = (*traineeRectanglesIterator)->getArea();
            
            //get intersection corners of the two rectangles
            
            
            //left edge
            if (keyX0 < checkX0)
            {
                inX0 = checkX0;
            }
            else
            {
                inX0 = keyX0;
            }
            
            // right edge
            if (keyX1 > checkX1)
            {
                inX1 = checkX1;
            }
            else
            {
                inX1 = keyX1;
            }
            
            //top edge
            if (keyY0 < checkY0)
            {
                inY0 = checkY0;
            }
            else
            {
                inY0 = keyY0;
            }
            
            //bottom edge
            if (keyY1 > checkY1)
            {
                inY1 = checkY1;
            }
            else
            {
                inY1 = keyY1;
            }
            
            //calculate the intersection area
            
            //if the intersection edges are out of order then there is not an
            //intersection so the area would be zero and this is not a matching rectangle
            if ( (inX0 > inX1) || (inY0 > inY1) )
            {
                continue;
            }
            else
            {
                inArea= (inX1-inX0) * (inY1-inY0);
                rectScore= inArea/(keyArea+checkArea-inArea);
                if ( expertRectangle->compareMatch2( rectScore ) )
                {
                    expertRectangle->setMatch2( (*traineeRectanglesIterator),rectScore );
                }
            }
            
        }
    }
}
