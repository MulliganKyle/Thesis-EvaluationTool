//
//  rectangle.hpp
//  Thesis-Evaluation-Tool
//
//  Created by Kyle Mulligan on 12/20/17.
//  Copyright © 2017 Kyle Mulligan. All rights reserved.
//

#ifndef rectangle_hpp
#define rectangle_hpp

#include <stdio.h>
#include <iostream>
#include <cmath>


#define DEF_VAL 0
#define DEF_TAG ""


class Rectangle
{
private:
//attributes of mediaItem
    
    // x coordinates of the corners of the rectangle
    int x0_;
    int x1_;
    
    // y coordinates of the corners of the rectangle
    int y0_;
    int y1_;
    
    //x and y coordinates of the center of the rectangle
    double centerX_;
    double centerY_;
    
    //area of the rectangle
    double area_;
    
    //the type of damage denoted by the rectangle
    std::string tag_;
    
    //the attributes used to match a rectangle to another rectangle
    Rectangle* match_;
    double matchCentXDiff_;
    double matchCentYDiff_;
    double matchAreaDiff_;
    
    //****************************//
    //class wide attributes       //
    //****************************//
    static int numberOfRects_;
    
public:
// methods of rectangle
    
    //constructors
    //
    Rectangle(int=DEF_VAL,
              int=DEF_VAL,
              int=DEF_VAL,
              int=DEF_VAL,
              std::string=DEF_TAG);
    
    //destructors
    //
    virtual ~Rectangle();
    
    
    
    //accessors
    //
    int getX0() const { return x0_; }
    int getX1() const { return x1_; }
    int getY0() const { return y0_; }
    int getY1() const { return y1_; }
    
    double getCenterX() const { return centerX_; }
    double getCenterY() const { return centerY_; }
    
    double getArea() const { return area_; }
    
    std::string getTag () const { return tag_; }
    
    Rectangle* getMatch () const { return match_; }
    double getMatchCentXDiff () const { return matchCentXDiff_; }
    double getMatchCentYDiff () const { return matchCentYDiff_; }
    double getMatchAreaDiff () const { return matchAreaDiff_; }
    
    int getNumberOfRects () const { return numberOfRects_; }
    
    
    
    //mutators
    //
    void setX0(int);
    void setX1(int);
    void setY0(int);
    void setY1(int);
    
    void setCenterX();
    void setCenterY();
    
    void setArea();
    
    void setTag(std::string);
    
    void setMatch(Rectangle*, double, double, double);
    
    
    //helpers
    //
    bool compareMatch(double, double, double);

};


#endif /* rectangle_hpp */



