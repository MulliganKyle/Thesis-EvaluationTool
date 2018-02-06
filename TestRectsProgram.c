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
    char name[1000];
    int xdim;
    int ydim;
    int numRects;
    struct rectangle rectArray[50];
    
};

int main (int argc, char **argv)
{
    FILE *inFile;
    struct img imgArray[500];
    
    char buff[BUFF_SIZE];
    char rec[]="rect:";
    char jpg[]="jpg";
    
    bool isRect;
    bool imgNameFound;
    
    
    int buffCount; //used to address into each line of characters from the file
    int rectCount=0; //counts the number of rectangles in an image
    int imgNameBuffCount; //used to look for .jpg file extension while acquiring img name
    int nameCount; //keeps track of where in the img name the characters are going
    int imgCount=0; //keeps track of how many images there are in the imgArray
    
    
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
                    //store the coordinates found in a rectangle struct array
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
                    //printf("made it 01\n");
                    //since not a rectangle, need to reset the buff count to 0
                    //to start looking for the image name from the beginning
                    buffCount=0;
                    imgNameFound=false;
                    nameCount=0;
                    while ( !imgNameFound )
                    {
                        //printf("made it 03\n");
                        //printf("%c\n",imgArray[imgCount].name[nameCount-1]);
                        // if the character isn't a period ( . ), put it into the name array for the img struct
                        if (buff[buffCount]!='.')
                        {
                            imgArray[imgCount].name[nameCount]=buff[buffCount];
                            nameCount++;
                        }
                        // if it is a period ( . ) assume the end of the img name
                        //has been found and check if the file extension .jpg is present.
                        else if (buff[buffCount]=='.')
                        {
                            //printf("made it 04\n");
                            //when a . is found assume that the end of the img name has been found
                            imgNameFound=true;
#if 0
                            //check the next three values in the buffer to see if they are the file extension .jpg
                            imgNameBuffCount=buffCount+1;
                            for (int i=0; i<3 && imgNameFound ; i++)
                            {
                                //if a mismatch is found then we have not found the end of the img name
                                if (jpg[i]!=buff[imgNameBuffCount])
                                {
                                    imgNameFound=false;
                                }
                            }
#endif
                        }
                        else if (buff[buffCount]=='\n' || buff[buffCount]=='\0')
                        {
                            imgNameFound=true;
                        }
                        // once the end of the img name is found, copy the
                        // file extension and string termination character
                        // into the end of the name array of the img struct
                        if (imgNameFound)
                        {
                            imgArray[imgCount].name[nameCount]='.';
                            imgArray[imgCount].name[nameCount+1]='j';
                            imgArray[imgCount].name[nameCount+2]='p';
                            imgArray[imgCount].name[nameCount+3]='g';
                            imgArray[imgCount].name[nameCount+4]='\0';
                        }
                        buffCount++;
                        
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
        puts(buff);
        fclose(inFile);
    }
    printf(" %d rectangles\n", imgArray[0].numRects);
    printf("x0: %d \ny0: %d\nx1: %d\ny1: %d\n", imgArray[0].rectArray[0].x0, imgArray[0].rectArray[0].y0, imgArray[0].rectArray[0].x1, imgArray[0].rectArray[0].y1);
    printf("img name: %s\n", imgArray[0].name);
    
    return 0;
}
