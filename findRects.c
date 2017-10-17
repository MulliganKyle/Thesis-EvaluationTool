//Kyle Mulligan

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#define BUFF_SIZE 256

int main (int argc, char **argv)
{
   FILE *inFile;
   char buff[BUFF_SIZE];
   char rec[]="rec";
   bool isRect;
   int rectNum=0;


   inFile=fopen("out.txt", "r");
   if (inFile==NULL)
   {
      perror("Error opening the file");
   }
   else
   {
      while( !feof(inFile) )
      {	 
	 if (fgets(buff, BUFF_SIZE, inFile) != NULL)
	 {
	    isRect=true;
	    if( buff[3]=='t')
	    {
	       for (int i=0; i<3; i++)
	       {
		  if ( buff[i]!=rec[i] )
		  {
		     isRect=false;
		  }
	       }

	       if (isRect)
	       {
		  rectNum++;
	       }
	    }
	 }
      }
      puts(buff);
      fclose(inFile);
   }
   printf(" %d rectangles\n", rectNum);
   return 0;
}
