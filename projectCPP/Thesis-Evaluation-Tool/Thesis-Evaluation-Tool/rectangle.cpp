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
                     int newTag)
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
    
    setMatch2(NULL, 0.0, 0.0, 0.0);
    
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

void Rectangle::setTag(int newTag)
{
    tag_=newTag;
}

void Rectangle::setMatch2(Rectangle* newMatch, double newMatchCentXDiff, double newMatchCentYDiff, double newMatchAreaDiff)
{
    match_=newMatch;
    matchCentXDiff_=newMatchCentXDiff;
    matchCentYDiff_=newMatchCentYDiff;
    matchAreaDiff_=newMatchAreaDiff;
}

void Rectangle::setMatch(Rectangle* newMatch, double newScore)
{
    match2_=newMatch;
    match2Score_= newScore;
}

//helper
//


//compare the current match to a new potential match.
//if the new match is better returns true.
//if there is no new match returns true.
//use the sum of the differences to determine if the new rectangle is better.
bool Rectangle::compareMatch2(double newMatchCentXDiff, double newMatchCentYDiff, double newMatchAreaDiff)
{
    double centerDelta;
    double areaDelta;
    
    double newCenterDelta;
    double newAreaDelta;
    //if there is no current match then return true.
    if ( match_ == NULL)
    {
        return true;
    }
    else
    {
        //to calculate the deltas, acquire the distance of the check center from the key center
        //divide by the distance to the corner of the key rectangle
        centerDelta = sqrt(pow(matchCentXDiff_,2)+pow(matchCentYDiff_,2)) /
        sqrt(pow( abs( x0_ - x1_ )/2,2) + pow( abs( y0_ - y1_ )/2,2));
        
        //to calculate the deltas of the area, divide the difference in areas by the key area
        
        areaDelta = matchAreaDiff_/area_;
        
        newCenterDelta = sqrt(pow(newMatchCentXDiff,2)+pow(newMatchCentYDiff,2)) /
        sqrt( pow( abs( x0_ - x1_ ),2) + pow( abs( y0_ - y1_ ),2));
        
        newAreaDelta = newMatchAreaDiff/area_;
        
        //compare the delta of the current best match to the delta of the new match and determine
        //if the new match is better.
        //if the new match is better return true
        //otherwise return false.
        if ( (centerDelta+areaDelta) > (newCenterDelta+newAreaDelta) )
        {
            return true;
        }
        else
        {
            return false;
        }
        
        
    }
}


bool Rectangle::compareMatch(double newMatchScore)
{
    if ( match_ == NULL)
    {
        return true;
    }
    else
    {
        if (newMatchScore > match2Score_)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}











