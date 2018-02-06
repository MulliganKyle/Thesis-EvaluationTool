//
//  rectangle.cpp
//  Thesis-Evaluation-Tool
//
//  Created by Kyle Mulligan on 12/20/17.
//  Copyright © 2017 Kyle Mulligan. All rights reserved.
//

#include "rectangle.hpp"


//class static attribute
//
int Rectangle::numberOfRects_=0;

//constructors
//
Rectangle::Rectangle(int newX0,
                     int newX1,
                     int newY0,
                     int newY1,
                     std::string newTag)
{
    if ( newX0 < newX1)
    {
        x0_=newX0;
        x1_=newX1;
    }
    else
    {
        x0_=newX1;
        x1_=newX0;
    }
    if ( newY0 < newY1)
    {
        y0_=newY0;
        y1_=newY1;
    }
    else
    {
        y0_=newY1;
        y1_=newY0;
    }
    
    setCenterX();
    setCenterY();
    
    setArea();
    
    tag_=newTag;
    
    numberOfRects_++;
}

//destructors
//

Rectangle::~Rectangle()
{
    numberOfRects_--;
}

//mutators
//

void Rectangle::setX0(int newX0)
{
    x0_=newX0;
}

void Rectangle::setX1(int newX1)
{
    x1_=newX1;
}

void Rectangle::setY0(int newY0)
{
    y0_=newY0;
}

void Rectangle::setY1(int newY1)
{
    y1_=newY1;
}


//calculate the center x coordinate
void Rectangle::setCenterX()
{
    if ( x0_< x1_ )
    {
        centerX_= (float)x0_ + (((float)x1_-(float)x0_)/2);
    }
    else
    {
        centerX_= (float)x1_ + (((float)x0_-(float)x1_)/2);
    }
}

//calculate the center y coordinate
void Rectangle::setCenterY()
{
    if ( y0_< y1_ )
    {
        centerY_= (float)y0_ + (((float)y1_-(float)y0_)/2);
    }
    else
    {
        centerY_= (float)y1_ + (((float)y0_-(float)y1_)/2);
    }
}

//calculate the area
void Rectangle::setArea()
{
    area_= (float) (abs( x0_ - x1_ ) * abs( y0_ - y1_ ));
}

void Rectangle::setTag(std::string newTag)
{
    tag_=newTag;
}






