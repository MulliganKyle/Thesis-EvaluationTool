//
//  evalLib.cpp
//  Thesis-Evaluation-Tool
//
//  Created by Kyle Mulligan on 1/23/18.
//  Copyright © 2018 Kyle Mulligan. All rights reserved.
//

#include "evalLib.hpp"




// This function reads a file and puts the information into the image list. no output, the list is
// the output and is changed through side effect. This avoids returning a copy of a large data list.
void getImgData(std::string filePath, std::list<Image*>& imageList)
{
    std::ifstream inFile;
    
    Image *newImage=NULL;
    
    
    std::string buff;
    std::string rec= "rect:";
    std::string tag;
    std::string imageName;
    std::string imageDims;
    
    std::string::size_type sz;
    
    //bool firstImage=true;
    
    int imageXDim;
    int imageYDim;
    
    int buffCount; // used to address into each line of characters from the file
    
    
    int coordinate;
    int coordArray[4];
    
    
    inFile.open(filePath, std::ifstream::in);
    if (!inFile.is_open())
    {
        std::cout << "Error opening file" <<std::endl;
    }
    
    else
    {
        
        while (std::getline(inFile, buff))
        {
            // check if the line is a rectangle
            if ( buff.compare(0,5,rec)==0)
            {
                buffCount=5;
                for (int j=0; j<4; j++)
                {
                    coordinate=0;
                    // at this point buffCount should denote the position in the buff right after "rect:"
                    // buffCount will increment until a ' ' (space) is found
                    // denoting the end of a coordinate
                    while (buff[buffCount]!=' ')
                    {
                        // create the int coordinate from the ascii characters in buff
                        coordinate=(coordinate*10)+(buff[buffCount]-'0');
                        buffCount++;
                    }
                    // at this point buffCount should be at a ' ' (space) in the buff
                    // so it must be incremented to the start of the next integer coordinate
                    buffCount++;
                    coordArray[j]=coordinate;
                }
                
                // create substr starting after the last coordinate, this will be the tag
                tag=buff.substr(buffCount+1);
                
                // add new rectangle to the most recent image. this will create a new rectangle and push
                // it to the back of the list held in new image. it will also calculate the center and area.
                newImage->addNewRectangle(coordArray[0], coordArray[2], coordArray[1], coordArray[3], tag);
                
                
            }
            else
            {
                /*
                // at this point, the previous image has had all of its rectangles found so a new image
                // needs to be processed. Before doing this, sort the list of rectangles from the
                // previous image, if there is a previous image. CONFUSINGLY, THE PREVIOUS IMAGE IS
                // STILL NAMED NEW IMAGE AT THIS POINT.
                if (firstImage)
                {
                    firstImage=false;
                }
                else
                {
                    newImage->sortRectangles();
                }
                 */
                // now the new image name and other information can be processed.
                
                
                //  create a substring of the image name, goes to the first space ' '
                imageName= buff.substr(0,buff.find(' '));
                
                // create substring of the dimensions
                imageDims= buff.substr(buff.find(' ')+1);
                
                // convert first set of numbers into the x dimension of the image
                imageXDim=std::stoi(imageDims,&sz);
                // convert the second set of numbers into the y dimension of the image
                imageYDim=std::stoi(imageDims.substr(sz+1));
                
                // create new image using the values obtained above.
                newImage = new Image(imageName,imageXDim,imageYDim);
                imageList.push_back(newImage);
                
                
            }
        }
    }
}

//Compare two input lists of images
//TODO DECIDE WHAT TO RETURN IF ANYTHING
void compareImages(const std::list<Image*>& keyImages, const std::list<Image*>& checkImages)
{
    std::list<Image*>::const_iterator keyImagesIterator;
    std::list<Image*>::const_iterator checkImagesIterator;
    
    std::list<Rectangle*>::iterator keyRectsIterator;
    std::list<Rectangle*>::iterator checkRectsIterator;
    
    std::list<Rectangle*> keyRects;
    std::list<Rectangle*> checkRects;
    
    double imageDimX;
    double imageDimY;
    
    double keyCenterX;
    double keyCenterY;
    double keyArea;
    double checkCenterX;
    double checkCenterY;
    double checkArea;
    
    
    
    // go through each image in the images lists
    for ( keyImagesIterator=keyImages.begin(), checkImagesIterator=checkImages.begin();
         keyImagesIterator!=keyImages.end() && checkImagesIterator!=checkImages.end();
         ++keyImagesIterator, ++checkImagesIterator)
    {
        // for each image, get all the rectangles
        keyRects=(*keyImagesIterator)->getAllRectangles();
        checkRects=(*checkImagesIterator)->getAllRectangles();
        
        //get the dimensions of the image for use later
        imageDimX=(*keyImagesIterator)->getXdim();
        imageDimY=(*keyImagesIterator)->getYdim();
        
        //for each rectangle in the key list, check against all rectangles in the check rectangles
        for ( keyRectsIterator=keyRects.begin(); keyRectsIterator!=keyRects.end(); ++keyRectsIterator)
        {
            for ( checkRectsIterator=checkRects.begin(); checkRectsIterator!=checkRects.end(); ++checkRectsIterator)
            {
                // TODO FIGURE OUT HOW TO ACTUALLY COMPARE TWO RECTANGLES AND PICK THE BEST ONE.
                // THEN FIGURE OUT WHAT TO DO IF THERE IS OVERLAP ON BEST RECTANGLES...
                //if the tags are not the same, this is not the correct rectangle so continue
                if ( (*keyRectsIterator)->getTag() != (*checkRectsIterator)->getTag() )
                {
                    continue;
                }
                //if the tags are the same, this may be the correct rectangle.
                else
                {
                    keyCenterX = (*keyRectsIterator)->getCenterX();
                    keyCenterY = (*keyRectsIterator)->getCenterY();
                    
                    checkCenterX = (*checkRectsIterator)->getCenterX();
                    checkCenterY = (*checkRectsIterator)->getCenterY();
                    
                    //if the center of the rectangle is close enough check area.
                    if ( (abs(keyCenterX-checkCenterX) <= (imageDimX*CENTER_PERCENT_ERROR)) &&
                         (abs(keyCenterY-checkCenterY) <= (imageDimY*CENTER_PERCENT_ERROR)) )
                    {
                        keyArea = (*keyRectsIterator)->getArea();
                        checkArea = (*checkRectsIterator)->getArea();
                        
                        //if the differences in area are close enough, then it is likely this rectangle
                        //is the correct one. store it somehow with a score maybe.
                        if( abs(keyArea-checkArea)<=(imageDimX*imageDimY*AREA_PERCENT_ERROR) )
                        {
                            
                        }
                        
                    }
                    
                }
            }
        }
    }
}

