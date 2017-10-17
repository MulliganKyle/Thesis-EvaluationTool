// Kyle Mulligan
// file search in c++
// not parallel




#include <iostream>
#include <fstream>
#include <numeric>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <string>

double dtime()
{
   double tseconds = 0.0;
   struct timeval mytime;
   gettimeofday(&mytime,(struct timezone*)0);
   tseconds = (double)(mytime.tv_sec + mytime.tv_usec*1.0e-6);
   return( tseconds );
}

int main(int argc, char **argv)
{
   std::ifstream inFile;
   std::string searchString;
   std::string numThreadsString;
   int bufferCount, strCount, chunkCount, chunkSize, numThreads;
   int strLen;
   int length;
   int correct;
   char * buffer;
   unsigned int strNum=0;
   double tstartT, tstopT, ttimeT;

   //set variables from command line
   if (argc == 4) 
   {
      inFile.open(argv[1]);
      numThreadsString=std::string(argv[2]);
      numThreads=std::stoi(numThreadsString);
      searchString=std::string(argv[3]); 
   }
   else 
   {
      std::cerr << "Usage: ./hw input_file numberOfLines stringToSearchFor" << std::endl;
      exit(1);
   }

   //make sure the file is open before doing anything
   if(inFile.is_open())
   {
      std::cout<<"successfully opened the file" << std::endl;

      //get length of file:
      inFile.seekg(0, inFile.end);
      length= inFile.tellg();
      inFile.seekg(0, inFile.beg);

      std::cout << "the file is " << length << " characters long." << std::endl;

      //allocate memory
      buffer=new char [length];

      //read the file into the buffer
      inFile.read(buffer, length);

      //determine the length of the string to search for
      strLen=searchString.length();

      //calculate chunk size as ciel(length/numThreads)
      chunkSize=(length+numThreads-1)/numThreads;






      //start timing
      tstartT = dtime();

      //do string search

#pragma omp parallel num_threads(numThreads) private(bufferCount, strCount, chunkCount, correct) shared( strNum)
#pragma omp for
      //private(chunkCount, bufferCount, strCount) shared(buffer, strNum)
      //loop for each chunk of the problem
      for ( chunkCount = 0; chunkCount < numThreads; chunkCount++)
      {
	 //loop throught the characters in each chunk plus extra characters equal to the
	 //search string length at the end of the chunk for a little bit of overlap
	 for ( bufferCount =0; bufferCount < (chunkSize+strLen-2); bufferCount++)
	 {
	    //loop through each character in the search string and compare to corresponding
	    //characters in the buffer to determine if the strings are a match
	    if( ((chunkCount*chunkSize)+bufferCount)< (length-strLen))
	    {
	       for ( strCount = 0, correct=1; strCount< strLen && correct ; strCount++)
	       {
		  //count how many characters match
		  if(searchString[strCount]!=buffer[(chunkCount*chunkSize)+bufferCount+strCount])
		  {
		     correct=0;
		  }
	       }
	       // if the number of characters that match is the same as the length of the search
	       // string then the string is a match
	       if(correct)
	       {
		  #pragma omp atomic
		  strNum++;
	       }
	    }
	 }
      }
      //stop timing
      tstopT=dtime();
      ttimeT=tstopT-tstartT;
      if ((ttimeT) > 0.0)
      {
	 std::cout << "using " << numThreads << " threads, finished searching in " << ttimeT << " seconds..." << "found \"" << searchString << "\" "<< strNum << " times. " << std::endl;
      }


      //start timing
      tstartT = dtime();
      strNum=0;

      //do string search

      //private(chunkCount, bufferCount, strCount) shared(buffer, strNum)
      //loop for each chunk of the problem
      for ( chunkCount = 0; chunkCount < numThreads; chunkCount++)
      {
	 //loop throught the characters in each chunk plus extra characters equal to the
	 //search string length at the end of the chunk for a little bit of overlap
	 for ( bufferCount =0; bufferCount < (chunkSize+strLen-2); bufferCount++)
	 {
	    //loop through each character in the search string and compare to corresponding
	    //characters in the buffer to determine if the strings are a match
	    if( ((chunkCount*chunkSize)+bufferCount)< (length-strLen))
	    {
	       for ( strCount = 0, correct=1; strCount< strLen && correct ; strCount++)
	       {
		  //count how many characters match
		  if(searchString[strCount]!=buffer[(chunkCount*chunkSize)+bufferCount+strCount])
		  {
		     correct=0;
		  }
	       }
	       // if the number of characters that match is the same as the length of the search
	       // string then the string is a match
	       if(correct)
	       {
		  strNum++;
	       }
	    }
	 }
      }
      //stop timing
      tstopT=dtime();
      ttimeT=tstopT-tstartT;
      if ((ttimeT) > 0.0)
      {
	 std::cout << "using serial computation, finished searching in " << ttimeT << " seconds..." << "found \"" << searchString << "\" "<< strNum << " times. " << std::endl;
      }

      delete[] buffer;


   }
   //give error if the file can't be open
   else
   {
      std::cerr << "ERROR: COULD NOT OPEN FILE" << std::endl;
   }

   inFile.close();


}
