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
    int valArray[5];
    
    
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
                for (int j=0; j<5; j++)
                {
                    coordinate=0;
                    // at this point buffCount should denote the position in the buff right after "rect:"
                    // buffCount will increment until a ' ' (space) is found
                    // denoting the end of a coordinate
                    while ((buff[buffCount]!=' ') && (buff[buffCount]!='\n') && buff[buffCount]!='\0')
                    {
                        // create the int coordinate from the ascii characters in buff
                        coordinate=(coordinate*10)+(buff[buffCount]-'0');
                        buffCount++;
                    }
                    // at this point buffCount should be at a ' ' (space) in the buff
                    // so it must be incremented to the start of the next integer coordinate
                    buffCount++;
                    valArray[j]=coordinate;
                }
                
                
                // create substr starting after the last coordinate, this will be the tag
                // tag=buff.substr(buffCount);
                
                
                
                // add new rectangle to the most recent image. this will create a new rectangle and push
                // it to the back of the list held in new image. it will also calculate the center and area.
                newImage->addNewRectangle(valArray[0], valArray[2], valArray[1], valArray[3], valArray[4]);
                
                
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
    
    bool foundMatch;
    
    
    
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
        
        
        //for each rectangle in the key list, check against all rectangles in the check rectangles list
        for ( keyRectsIterator=keyRects.begin(); keyRectsIterator!=keyRects.end(); ++keyRectsIterator)
        {
            //for a new rectangle in the key list, set the foundMatch to false until a match is found
            foundMatch=false;
            
            for ( checkRectsIterator=checkRects.begin(); checkRectsIterator!=checkRects.end(); ++checkRectsIterator)
            {

                //if the tags are not the same, this is not the correct rectangle so continue
                if ( ((*keyRectsIterator)->getTag()) != ((*checkRectsIterator)->getTag() ))
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
                        
                        //if the differences in area are close enough, then it is likely this
                        //rectangle is the correct one. store the match into the key
                        //rectangle. after checking against any previous match.
                        if( abs(keyArea-checkArea)<=(imageDimX*imageDimY*AREA_PERCENT_ERROR) )
                        {
                            //check if this new match is a better match than the current match
                            //if there is a current match. if the compare comes back true,
                            //then the new match is better and should be stored.
                            if ( (*keyRectsIterator)->compareMatch( abs(keyCenterX-checkCenterX),
                                                                   abs(keyCenterY-checkCenterY),
                                                                   abs(keyArea-checkArea)) )
                            {
                                (*keyRectsIterator)->setMatch( (*checkRectsIterator),
                                                              abs(keyCenterX-checkCenterX),
                                                              abs(keyCenterY-checkCenterY),
                                                              abs(keyArea-checkArea) );
                            }
                            foundMatch=true;
                        }
                    }
                }
            }
            //if a match was found then add one to the score of that image. the total score will be
            //number of matches over number of rectangles.
            //this only happens once per rectangle in an image.
            if (foundMatch)
            {
                (*keyImagesIterator)->increaseNumMatches();
            }
        }
    }
}

/*******************************************************************************/
/* other compare images function:*/
/*******************************************************************************/

//Compare two input lists of images

void compareImages2(const std::list<Image*>& keyImages, const std::list<Image*>& checkImages)
{
    std::list<Image*>::const_iterator keyImagesIterator;
    std::list<Image*>::const_iterator checkImagesIterator;
    
    std::list<Rectangle*>::iterator keyRectsIterator;
    std::list<Rectangle*>::iterator checkRectsIterator;
    
    std::list<Rectangle*> keyRects;
    std::list<Rectangle*> checkRects;
    
    double imageDimX;
    double imageDimY;
    
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
    
    bool foundMatch;
    
    
    
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
        
        
        //for each rectangle in the key list, check against all rectangles in the check rectangles list
        for ( keyRectsIterator=keyRects.begin(); keyRectsIterator!=keyRects.end(); ++keyRectsIterator)
        {
            //for a new rectangle in the key list, set the foundMatch to false until a match is found
            foundMatch=false;
            
            for ( checkRectsIterator=checkRects.begin(); checkRectsIterator!=checkRects.end(); ++checkRectsIterator)
            {
                
                //if the tags are not the same, this is not the correct rectangle so continue
                if ( ((*keyRectsIterator)->getTag()) != ((*checkRectsIterator)->getTag() ))
                {
                    continue;
                }
                //if the tags are the same, this may be the correct rectangle.
                else
                {
                    //get the corners of the rectangles and the areas
                    keyX0 = (*keyRectsIterator)->getX0();
                    keyX1 = (*keyRectsIterator)->getX1();
                    keyY0 = (*keyRectsIterator)->getY0();
                    keyY1 = (*keyRectsIterator)->getY1();
                    keyArea = (*keyRectsIterator)->getArea();
                    
                    checkX0 = (*checkRectsIterator)->getX0();
                    checkX1 = (*checkRectsIterator)->getX1();
                    checkY0 = (*checkRectsIterator)->getY0();
                    checkY1 = (*checkRectsIterator)->getY1();
                    checkArea = (*checkRectsIterator)->getArea();
                    
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
                    
                    //if the intersection areas are reversed then there is not an
                    //intersection so the area would be zero and this is not a matching rectangle
                    if ( (inX0 > inX1) || (inY0 > inY1) )
                    {
                        continue;
                    }
                    else
                    {
                        inArea= (inX1-inX0) * (inY1-inY0);
                        rectScore= inArea/(keyArea+checkArea-inArea);
                        if ( (*keyRectsIterator)->compareMatch2( rectScore ) )
                        {
                            (*keyRectsIterator)->setMatch2( (*checkRectsIterator),rectScore );
                        }
                        foundMatch=true;
                    }
                    
                }
            }
            //if a match was found then score to to the total score of that image.
            //the total score will be
            //total score over number of rectangles.
            //this only happens once per rectangle in an image.
            if (foundMatch)
            {
                (*keyImagesIterator)->increaseNumMatches2( (*keyRectsIterator)->getMatch2score() );
            }
        }
    }
}
