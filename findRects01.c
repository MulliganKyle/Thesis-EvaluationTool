//
//  findRects01.c
//  
//
//  Created by Kyle Mulligan on 11/13/17.
//

#include "findRects01.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#define BUFF_SIZE 256




void findRects( img imgArray[], char filePath[] )
{
    FILE *inFile;
    
    char buff[BUFF_SIZE];
    char rec[]="rect:";
    char jpg[]="jpg";
    
    bool isRect;
    bool imgNameFound;
    bool xfound;
    
    
    int buffCount; //used to address into each line of characters from the file
    int rectCount=0; //counts the number of rectangles in an image
    int imgNameBuffCount; //used to look for .jpg file extension while acquiring img name
    int nameCount; //keeps track of where in the img name the characters are going
    int imgCount=0; //keeps track of how many images there are in the imgArray
    int tagCount; //keeps track of where in the 'tag' char array to put characters
    
    
    int coordinate;
    int coordArray[4];
    
    
    
    inFile=fopen(filePath, "r");
    if (inFile==NULL)
    {
        perror("Error opening the file: ");
    }
    else
    {
        while( !feof(inFile) )
        {
            //read a line from the file
            if (fgets(buff, BUFF_SIZE, inFile) != NULL)
            {
                //Check if this line denotes a rectangle
                //The first five characters should be "rect:"
                //After this loop buffCount will be 5, the character right after "rect:"
                //which should be an ascii character representing a number 0-9
                //rectangle is assumed to be true until proved otherwise
                isRect=true;
                for (buffCount=0; buffCount<5 && isRect; buffCount++)
                {
                    //check characters against the string "rect:"
                    if ( buff[buffCount]!=rec[buffCount] )
                    {
                        isRect=false;
                    }
                }
                //printf("made it 02\n");
                
                /////////////////////////////////////////////////////////////////////////////////////
                //if the line denotes a rectangle, acquire the coordinate of the rectangle's corners.
                /////////////////////////////////////////////////////////////////////////////////////
                if (isRect)
                {
                    //get the coordinates x0,y0 and x1,y1
                    for (int j=0; j<4; j++)
                    {
                        coordinate=0;
                        //at this point buffCount should denote the position in the buff right after "rect:"
                        //buffCount will increment until a ' ' (space) is found
                        //denoting the end of a coordinate
                        while (buff[buffCount]!=' ')
                        {
                            //create the int coordinate from the ascii characters in buff
                            coordinate=(coordinate*10)+(buff[buffCount]-'0');
                            buffCount++;
                        }
                        //at this point buffCount should be at a ' ' (space) in the buff
                        //so it must be incremented to the start of the next integer coordinate
                        buffCount++;
                        coordArray[j]=coordinate;
                    }
                    /*
                    tagCount=0;
                    while (buff[buffCount]!='\n')
                    {
                        imgArray[imgCount-1].rectArray[rectCount].tag[tagCount]=buff[buffCount];
                        tagCount++;
                        buffCount++;
                    }
                    */
                    
                    //store the coordinates found in a rectangle struct array
                    //putting them into imgArray[imgCount-1] because each time
                    //a new image is found, imgCount is incremented and would address
                    //a position in the imgArray thats one more than the current img.
                    imgArray[imgCount-1].rectArray[rectCount].x0=coordArray[0];
                    imgArray[imgCount-1].rectArray[rectCount].y0=coordArray[1];
                    imgArray[imgCount-1].rectArray[rectCount].x1=coordArray[2];
                    imgArray[imgCount-1].rectArray[rectCount].y1=coordArray[3];
                    //increment the number of rectangles found
                    rectCount++;
                }
                
                /////////////////////////////////////////////////////////////////////////
                //if the line is not a rectangle then it must be an img name so get that.
                /////////////////////////////////////////////////////////////////////////
                else
                {
                    //since not a rectangle, need to reset the buff count to 0
                    //to start looking for the image name from the beginning
                    buffCount=0;
                    imgNameFound=false;
                    nameCount=0;
                    while ( !imgNameFound )
                    {
                        // if the character isn't a space ' ', put it into the name array for the img struct
                        if (buff[buffCount]!=' ')
                        {
                            imgArray[imgCount].name[nameCount]=buff[buffCount];
                            nameCount++;
                        }
                        // if it is a space ' '  assume the end of the img name has been found.
                        else
                        {
                            //when a ' ' is found assume that the end of the img name has been found
                            imgNameFound=true;
                            
                        }
                        
                        buffCount++;
                        
                        // once the end of the img name is found,
                        //acquire the dimensions of the images.
                        
                        if (imgNameFound)
                        {
                            xfound=false;
                            imgArray[imgCount].xdim=0;
                            imgArray[imgCount].ydim=0;
                                                        
                            while ( buff[buffCount]!= '\n' )
                            {
                                if ( buff[buffCount]!='x')
                                {
                                    
                                    if (!xfound)
                                    {
                                        imgArray[imgCount].xdim= (imgArray[imgCount].xdim*10) + (buff[buffCount]-'0');
                                    }
                                    else
                                    {
                                        imgArray[imgCount].ydim= (imgArray[imgCount].ydim*10) + (buff[buffCount]-'0');
                                    }
                                }
                                else
                                {
                                    xfound = true;
                                }
                                buffCount++;
                                
                            }
                            
                        }
                        
                        
                    }
                    //since a new image has been found, store the number of rectangles in the previous img struct
                    //as long as this is not the first img
                    if(imgCount!=0)
                    {
                        imgArray[imgCount-1].numRects=rectCount;
                    }
                    
                    
                    //since a new image has been found, there are no rectangles in it so reset rectCount
                    rectCount=0;
                    
                    //increment the img count
                    imgCount++;
                    
                }
            }
        }
        //put the number of rectangles into the last image struct after the end of file is found.
        imgArray[imgCount-1].numRects=rectCount;
        fclose(inFile);
    }
    
}
