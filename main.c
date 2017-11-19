//
//  main.c
//  
//
//  Created by Kyle Mulligan on 11/14/17.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "findRects01.h"


int main ()
{
    img * instructorImgArray = malloc ( sizeof(img)*DATACOUNT );
    if ( instructorImgArray==NULL )
    {
        perror("Error malloc failed: ");
        exit(1);
    }
    else
    {
        memset( instructorImgArray, 0, (sizeof(img)*DATACOUNT) );
    }
    //img * studentImgArray = malloc ( sizeof(img)*DATACOUNT );
    
    
    findRects(instructorImgArray, "out.txt");
    
    printf(" %d rectangles\n", instructorImgArray[0].numRects);
    printf("x0: %d \ny0: %d\nx1: %d\ny1: %d\n", instructorImgArray[0].rectArray[0].x0, instructorImgArray[0].rectArray[0].y0, instructorImgArray[0].rectArray[0].x1, instructorImgArray[0].rectArray[0].y1);
    printf("tag: %s\n", instructorImgArray[0].rectArray[0].tag);
    printf("img name: %s\n", instructorImgArray[0].name);
    printf("xdim: %d \nydim: %d \n", instructorImgArray[0].xdim, instructorImgArray[0].ydim);
    
    
    free(instructorImgArray);
}
