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

int main (int argc, char **argv)
{
    FILE *inFile;
    struct rectangle rectArray[1000];
    
    char buff[BUFF_SIZE];
    char rec[]="rect:";
    
    bool isRect;
    
    int coordinate;
    int buffCount;
    int rectCount=0;
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
                isRect=true;
                for (buffCount=0; buffCount<5 && isRect; buffCount++)
                {
                    //check characters against the string "rect:"
                    if ( buff[buffCount]!=rec[buffCount] )
                    {
                        isRect=false;
                    }
                }
                
                //if the line denotes a rectangle, acquire the coordinate of the rectangle's corners.
                if (isRect)
                {
                    //get the coordinates x0,y0 and x1,y1
                    for (int j=0; j<4; j++)
                    {
                        coordinate=0;
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
                }
                else
                {
                    //TODO handle each image and figure out how many rectangles per image plus image pixel size
                    
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
