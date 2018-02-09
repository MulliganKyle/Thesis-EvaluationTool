//
//  image.hpp
//  Thesis-Evaluation-Tool
//
//  Created by Kyle Mulligan on 12/20/17.
//  Copyright © 2017 Kyle Mulligan. All rights reserved.
//

#ifndef image_hpp
#define image_hpp

#include <stdio.h>
#include <list>


#include "rectangle.hpp"
#include "helperLib.hpp"

#define DEF_NAME ""


class Image
{
    
private:
//attributes of Image
//
    std::string name_;
    
    int xdim_;
    int ydim_;
    
    int numRects_;
    
    int numMatches_;
    
    std::list<Rectangle*> rectangleList_;
    

    //***************************//
    //class wide attributes      //
    //***************************//
    static int numberOfImages_;
    
public:
//methods of Image
//
    
    //constructors
    //
    Image(std::string = DEF_NAME,
          int = DEF_VAL,
          int = DEF_VAL);
    
    //destructors
    //
    virtual ~Image();
    
    //accessors
    //
    std::string getName() const { return name_;}
    
    int getXdim() const { return xdim_;}
    int getYdim() const { return ydim_;}
    
    int getNumRects() const {return numRects_;}
    int getNumMatches() const {return numMatches_;}
    
    std::list<Rectangle*> getAllRectangles() const { return rectangleList_; }
    
    
    //mutators
    //
    void setName(std::string);
    void setXdim(int);
    void setYdim(int);
    
    void addNewRectangle(int, int, int, int, std::string);
    void increaseNumMatches();
    
    //helpers
    //
    void sortRectangles();
    
    
    
};




#endif /* image_hpp */
