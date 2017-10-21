//Kyle Mulligan

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#define BUFF_SIZE 256

struct rectangle
{
    int x0;
    int y0;
    int x1;
    int y1;
};

struct img
{
    char name[50];
    int numberOfRects;
    
}

int main (int argc, char **argv)
{
    FILE *inFile;
    struct rectangle rectArray[1000];
    
    char buff[BUFF_SIZE];
    char rec[]="rect:";
    char jpg[]="jpg";
    
    bool isRect;
    bool imgNameFound;
    
    
    int buffCount;
    int rectCount=0;
    int imgRectCount=0;
    int imgNameBuffCount;
    
    
    int coordinate;
    int coordArray[4];
    
    
    
    inFile=fopen("out.txt", "r");
    if (inFile==NULL)
    {
        perror("Error opening the file");
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
                isRect=TRUE;
                for (buffCount=0; buffCount<5 && isRect; buffCount++)
                {
                    //check characters against the string "rect:"
                    if ( buff[buffCount]!=rec[buffCount] )
                    {
                        isRect=FALSE;
                    }
                }
                
                //if the line denotes a rectangle, acquire the coordinate of the rectangle's corners.
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
                    //store the coordinates found in a rectangle struct array
                    rectArray[rectCount].x0=coordArray[0];
                    rectArray[rectCount].y0=coordArray[1];
                    rectArray[rectCount].x1=coordArray[2];
                    rectArray[rectCount].y1=coordArray[3];
                    //increment the number of rectangles found
                    rectCount++;
                    imgRectCount++;
                }
                else
                {
                    buffCount=0;
                    imgNameFound=FALSE;
                    while ( !imgNameFound )
                    {
                        //TODO COPY CHARACTERS INTO AN IMAGE STRUCT
                        if (buff[buffCount]=='.')
                        {
                            //when a . is found assume that the end of the img name has been found
                            imgNameFound=TRUE;
                            
                            //check the next three values in the buffer to see if they are the file extension .jpg
                            imgNameBuffCount=buffCount+1;
                            for (int i=0; i<0 && imgNameFound ; i++)
                            {
                                //if a mismatch is found then we have not found the end of the img name
                                if (jpg[i]!=buff[imgNameBuffCount])
                                {
                                    imgNameFound=FALSE;
                                }
                            }
                        }
                        //TODO COPY THE LAST 3 CHARACTERS INTO IMAGE STRUCT WHEN JPG IS FOUND
                        buffCount++;
                        
                    }
                    //TODO STORE THE NUMBER OF RECTS FOR THE IMG CURRENT LAYOUT MEAN IMGRECTCOUNT HAS THE NUMBER FROM THE LAST IMG AT THIS POINT.
                    imgRectCount=0;
                    
                }
                
            }
        }
        puts(buff);
        fclose(inFile);
    }
    printf(" %d rectangles\n", rectCount);
    printf("x0: %d \ny0: %d\nx1: %d\ny1: %d\n", rectArray[1].x0, rectArray[1].y0, rectArray[1].x1, rectArray[1].y1);
    return 0;
}
