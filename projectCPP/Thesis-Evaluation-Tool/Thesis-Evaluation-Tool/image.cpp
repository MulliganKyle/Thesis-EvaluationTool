//
//  image.cpp
//  Thesis-Evaluation-Tool
//
//  Created by Kyle Mulligan on 12/20/17.
//  Copyright © 2017 Kyle Mulligan. All rights reserved.
//

#include "image.hpp"

//class static attribute
//
int Image::numberOfImages_=0;

//constructors
//

Image::Image(std::string newName,
             int newXDim,
             int newYDim)
{
    name_ = newName;
    xdim_ = newXDim;
    ydim_ = newYDim;
    numRects_=0;
    numMatches_=0;
    numberOfImages_ ++;
}


//destructors
//

Image::~Image()
{
    numberOfImages_ --;
}

//mutators
//

void Image::setName(std::string newName)
{
    name_=newName;
}

void Image::setXdim(int newXDim)
{
    xdim_=newXDim;
}

void Image::setYdim(int newYDim)
{
    ydim_=newYDim;
}


void Image::addNewRectangle(int x0, int x1, int y0, int y1, int tag)
{
    Rectangle *newRectangle = new Rectangle(x0, x1, y0, y1, tag);
    rectangleList_.push_back(newRectangle);
    numRects_++;
    
}

void Image::increaseNumMatches()
{
    numMatches_++;
}

//helpers
//
void Image::sortRectangles()
{
    rectangleList_.sort(compareRec);
}
