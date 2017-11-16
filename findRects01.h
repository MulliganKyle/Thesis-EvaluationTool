//
//  findRects01.h
//  
//
//  Created by Kyle Mulligan on 11/13/17.
//

#ifndef findRects01_h
#define findRects01_h

#include <stdio.h>

typedef struct
{
    int x0;
    int y0;
    int x1;
    int y1;
    
    //the type of damage denoted by the rectangle
    //char tag[50];
    
}rectangle;

typedef struct
{
    char name[1000];
    
    //dimensions of the image
    int xdim;
    int ydim;
    
    //number of rectangles with the image
    int numRects;
    
    //the rectangles associated with the image
    rectangle rectArray[50];
    
}img;


void findRects(img *, char*);





#endif /* findRects01_h */


