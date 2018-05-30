//
//  compareLib.cpp
//  Thesis-Evaluation-Tool
//
//  Created by Kyle Mulligan on 5/9/18.
//  Copyright © 2018 Kyle Mulligan. All rights reserved.
//

#include "compareLib.hpp"





//Compare two input lists of images


/*******************************************************************************/
/*******************************************************************************/
/**                                                                           **/
/**                                                                           **/
/**                 functions for comparing images in serial                  **/
/**                                                                           **/
/**                                                                           **/
/*******************************************************************************/
/*******************************************************************************/
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

void imageCompareSerialExperts(std::list<Image*> traineeImages, std::list<Image*> expertImages)
{
    std::list<Image*>::const_iterator traineeImagesIterator;
    std::list<Image*>::const_iterator expertImagesIterator;
    bool found;
    
    for ( expertImagesIterator=expertImages.begin(); expertImagesIterator!=expertImages.end(); ++expertImagesIterator)
    {
        for(traineeImagesIterator=traineeImages.begin(), found=false; traineeImagesIterator!=traineeImages.end() && !found; ++traineeImagesIterator)
        {
            //compare the names of the images
            if ( (*traineeImagesIterator)->getName().compare((*expertImagesIterator)->getName()) == 0 )
            {
                rectangleCompareSerial( (*traineeImagesIterator), (*expertImagesIterator));
                found=true;
            }
        }
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
        expertImage->increaseNumMatches2((*expertRectanglesIterator)->getMatchscore());
    }
    
    
}




//function that actually does the comparisons
void traineeRectangleCompare( Image* traineeImage, Rectangle* expertRectangle)
{
    std::list<Rectangle*> traineeRectangles = traineeImage->getAllRectangles();
    std::list<Rectangle*>::iterator traineeRectanglesIterator;
    
    double expertX0;
    double expertX1;
    double expertY0;
    double expertY1;
    double expertArea;
    
    double traineeX0;
    double traineeX1;
    double traineeY0;
    double traineeY1;
    double traineeArea;
    
    double inX0;
    double inX1;
    double inY0;
    double inY1;
    double inArea;
    
    double rectScore;
    
    for ( traineeRectanglesIterator=traineeRectangles.begin(); traineeRectanglesIterator!=traineeRectangles.end(); ++traineeRectanglesIterator)
    {
        
        //if the tags are not the same, this is not the correct rectangle so continue
        /* if ( (expertRectangle->getTag()) != ((*traineeRectanglesIterator)->getTag() ))
         {
         continue;
         }
         //if the tags are the same, this may be the correct rectangle.
         else
         {*/
        //get the edges of the rectangles and the areas
        expertX0 = expertRectangle->getX0();
        expertX1 = expertRectangle->getX1();
        expertY0 = expertRectangle->getY0();
        expertY1 = expertRectangle->getY1();
        expertArea = expertRectangle->getArea();
        
        traineeX0 = (*traineeRectanglesIterator)->getX0();
        traineeX1 = (*traineeRectanglesIterator)->getX1();
        traineeY0 = (*traineeRectanglesIterator)->getY0();
        traineeY1 = (*traineeRectanglesIterator)->getY1();
        traineeArea = (*traineeRectanglesIterator)->getArea();
        
        //get intersection corners of the two rectangles
        
        
        //left edge
        if (expertX0 < traineeX0)
        {
            inX0 = traineeX0;
        }
        else
        {
            inX0 = expertX0;
        }
        
        // right edge
        if (expertX1 > traineeX1)
        {
            inX1 = traineeX1;
        }
        else
        {
            inX1 = expertX1;
        }
        
        //top edge
        if (expertY0 < traineeY0)
        {
            inY0 = traineeY0;
        }
        else
        {
            inY0 = expertY0;
        }
        
        //bottom edge
        if (expertY1 > traineeY1)
        {
            inY1 = traineeY1;
        }
        else
        {
            inY1 = expertY1;
        }
        
        //calculate the intersection area
        
        //if the intersection edges are out of order then there is not an
        //intersection so the area would be zero and this is not a matching rectangle
        //otherwise there is an overlap and jaccard's index can be calculated
        if ( (inX0 < inX1) && (inY0 < inY1) )
        {
            inArea= (inX1-inX0) * (inY1-inY0);
            
            //jaccard's index
            rectScore= inArea/((expertArea+traineeArea)-inArea);
            
            //check if a match already exists and compare the two if they do.
            if ( expertRectangle->compareMatch( rectScore ) )
            {
                expertRectangle->setMatch( (*traineeRectanglesIterator),rectScore );
            }
        }
        
        //}
    }
}


/*******************************************************************************/
/*******************************************************************************/
/**                                                                           **/
/**                                                                           **/
/**   functions for comparing images in parallel using thread per some        **/
/**                             number of images                              **/
/**                                                                           **/
/*******************************************************************************/
/*******************************************************************************/

//creates threads to compare images
void imageCompareParallelWrapper(std::vector<Image*> traineeImages, std::vector<Image*> expertImages, int numThreads)
{
    std::vector<std::thread> threadVec;
    
    int threadCount;
    
    
    
    threadVec.reserve(numThreads);
    //spawn the designated number of threads
    for (threadCount=0; threadCount < numThreads; ++threadCount)
    {
        threadVec.push_back(std::thread(imageCompareParallel, traineeImages, expertImages, numThreads, threadCount));
        
    }
    
    //join the threads
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
        //uses the serial rectangle comparison
        rectangleCompareSerial( traineeImages[img], expertImages[img]);
    }
    
    
}


/*******************************************************************************/
/*******************************************************************************/
/**                                                                           **/
/**                                                                           **/
/**   functions for comparing images in parallel using thread per rectangle   **/
/**                                                                           **/
/**                                                                           **/
/*******************************************************************************/
/*******************************************************************************/
/*
 void imageCompareSerialRectangleParallel(std::list<Image*> traineeImages, std::list<Image*> expertImages)
 {
 std::list<Image*>::const_iterator traineeImagesIterator;
 std::list<Image*>::const_iterator expertImagesIterator;
 
 for ( expertImagesIterator=expertImages.begin(), traineeImagesIterator=traineeImages.begin();
 expertImagesIterator!=expertImages.end() && traineeImagesIterator!=traineeImages.end();
 ++expertImagesIterator, ++traineeImagesIterator)
 {
 rectangleCompareParallel( (*traineeImagesIterator), (*expertImagesIterator));
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
 */
/*******************************************************************************/
/*******************************************************************************/
/**                                                                           **/
/**                                                                           **/
/**   functions for comparing images in parallel using thread per Image to    **/
/**                     spawn a thread per rectangle                          **/
/**                                                                           **/
/*******************************************************************************/
/*******************************************************************************/

void rectangleCompareParallel(std::list<Image*> traineeImages, std::list<Image*> expertImages)
{
    std::list<Image*>::iterator expertImagesIterator;
    std::list<Image*>::iterator traineeImagesIterator;
    
    std::list<Rectangle*> expertRects;
    
    std::list<Rectangle*>::iterator expertRectsIterator;
    
    std::vector<std::thread> threadVec;
    
    size_t numImgs =expertImages.size();
    
    threadVec.reserve(numImgs);
    
    for (expertImagesIterator=expertImages.begin(), traineeImagesIterator=traineeImages.begin();
         expertImagesIterator!=expertImages.end() && traineeImagesIterator!=traineeImages.end();
         ++expertImagesIterator, ++traineeImagesIterator)
    {
        // for each image, get all the rectangles
        expertRects=(*expertImagesIterator)->getAllRectangles();
        
        //for each rectangle in the key list, check against all rectangles in the check rectangles list
        for ( expertRectsIterator=expertRects.begin(); expertRectsIterator!=expertRects.end(); ++expertRectsIterator)
        {
            //for each rectangle in each expert image spawn thread that runs traineeRectangleCompare
            threadVec.push_back(std::thread(traineeRectangleCompare, (*traineeImagesIterator), (*expertRectsIterator) ));
        }
        
    }
    
    //join the threads
    while ( !threadVec.empty() )
    {
        (threadVec.back()).join();
        threadVec.pop_back();
    }
    
    //put the rectangle scores into each image
    for (expertImagesIterator=expertImages.begin(), traineeImagesIterator=traineeImages.begin();
         expertImagesIterator!=expertImages.end() && traineeImagesIterator!=traineeImages.end();
         ++expertImagesIterator, ++traineeImagesIterator)
    {
        // for each image, get all the rectangles
        expertRects=(*expertImagesIterator)->getAllRectangles();
        
        //for each rectangle in the key list, check against all rectangles in the check rectangles list
        for ( expertRectsIterator=expertRects.begin(); expertRectsIterator!=expertRects.end(); ++expertRectsIterator)
        {
            //for each image spawn thread that runs rectangleCompareParallel above which
            //in turn spanws a thread per rectangle in the expert image.
            (*expertImagesIterator)->increaseNumMatches2((*expertRectsIterator)->getMatchscore());
        }
        
    }
}


/*******************************************************************************/
/*******************************************************************************/
/**                                                                           **/
/**                                                                           **/
/**     functions for reading and comparing multiple files for use in         **/
/**                           parallel file method                            **/
/**                                                                           **/
/*******************************************************************************/
/*******************************************************************************/

void multiFileTest(std::string filesPath, int threadID, int numThreads, int numFiles)
{
    std::ofstream outputFile;
    
    std::string resultsName;
    std::string traineeFileName;
    std::string expertFileName;
    std::string traineeFileInPath;
    std::string expertFileInPath;
    std::string resultsFileOutPath;
    
    
    std::list<Image*> traineeImages;
    std::list<Image*> expertImages;
    std::list<Image*>::iterator imagesIterator;
    
    Image* imagePTR;
    
    int j, k;
    
    double imageScore, fileScore, filePercent;
    
    
    int blockSize=numFiles/numThreads;
    int start=threadID*(blockSize);
    int end;
    if (threadID!=(numThreads-1))
    {
        end=start+blockSize;
    }
    else
    {
        end=numFiles;
    }
    
    expertFileInPath=filesPath+"4/"+"expert.txt";
    getImgData(expertFileInPath, expertImages);
    
    for (j = start; j<end; j++)
    {
        
        if (j<10)
        {
            traineeFileName ="out00"+std::to_string(j)+".txt";
            resultsName="results00"+std::to_string(j)+".txt";
        }
        else if (j < 100)
        {
            traineeFileName ="out0"+std::to_string(j)+".txt";
            resultsName="results0"+std::to_string(j)+".txt";
        }
        else
        {
            traineeFileName ="out"+std::to_string(j)+".txt";
            resultsName="results"+std::to_string(j)+".txt";
        }
        
        traineeFileInPath = filesPath+"4/"+traineeFileName;
        resultsFileOutPath = filesPath+"4/"+resultsName;
        
        getImgData(traineeFileInPath, traineeImages);
        
        
        outputFile.open(resultsFileOutPath, std::ofstream::out);
        if (!outputFile.is_open())
        {
            std::cout << "Error opening file" <<std::endl;
            return;
        }
        
        
        //compare images
        imageCompareSerial(traineeImages, expertImages);
        
        //output data to file
        for ( imagesIterator= expertImages.begin(), k=1, fileScore=0; imagesIterator!=expertImages.end(); ++imagesIterator, k++)
        {
            outputFile << "img " << k << ": " << (*imagesIterator)->getName() << " score: " << (*imagesIterator)->getNumMatches() << " / " << (*imagesIterator)->getNumRects() << std::endl;
            
            imageScore=(*imagesIterator)->getNumMatches()/(*imagesIterator)->getNumRects();
            fileScore+=imageScore;
        }
        
        filePercent=fileScore/(k-1);
        outputFile << std::endl << std::endl << "Comparison completed successfully using jaccard index." << std::endl;
        
        outputFile << "The total score for the submission is: " << fileScore << " / " << k-1 << " or " << filePercent*100 << "%" << std::endl;
        
        outputFile.close();
        
        //clean experts images and delete trainee images
        for ( imagesIterator= expertImages.begin(); imagesIterator!=expertImages.end(); ++imagesIterator)
        {
            (*imagesIterator)->clean();
        }
        while ( !traineeImages.empty() )
        {
            imagePTR = traineeImages.back();
            traineeImages.pop_back();
            delete imagePTR;
        }
    }
    
    //delete expert images before exiting
    while ( !expertImages.empty() )
    {
        imagePTR = expertImages.back();
        expertImages.pop_back();
        delete imagePTR;
    }
    
    
}










