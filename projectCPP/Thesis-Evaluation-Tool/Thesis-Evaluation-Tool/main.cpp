//
//   main.cpp
//   Thesis-Evaluation-Tool
//
//   Created by Kyle Mulligan on 12/20/17.
//   Copyright © 2017 Kyle Mulligan. All rights reserved.
//

#include <iostream>
#include <list>
#include <fstream>

#include "image.hpp"
#include "rectangle.hpp"
#include "evalLib.hpp"
#include "compareLib.hpp"

#define NUM_THREADS 4

int main(int argc, const char * argv[])
{
    
    std::ofstream JSFile;
    std::ofstream JPRFile;
    std::ofstream JPIFile;
    std::ofstream JPIRFile;

    
        std::list<Image*>::const_iterator keyImagesIterator;
    std::list<Image*> keyImagesSerial;
    std::list<Image*> test1ImagesSerial;
    
    std::list<Image*> keyImagesParallelR;
    std::list<Image*> test1ImagesParallelR;
    
    std::list<Image*> keyImagesParallelI;
    std::list<Image*> test1ImagesParallelI;
    
    std::list<Image*> keyImagesParallelIR;
    std::list<Image*> test1ImagesParallelIR;
    
    std::vector<Image*> keyImgVec;
    std::vector<Image*> checkImgVec;
    
    double tstart, tstop, ttime;
    
    int i;
    

    
    std::string expertFileIn="/Users/kyle/Documents/Thesis-EvaluationTool/generate_data/moreTestData/expertData01.txt";
    std::string traineeFileIn="/Users/kyle/Documents/Thesis-EvaluationTool/generate_data/moreTestData/traineeData01.txt";
    
    std::string jaccardSerial="/Users/kyle/Documents/Thesis-EvaluationTool/jaccardSerialOut.txt";
    std::string jaccardParallelRects="/Users/kyle/Documents/Thesis-EvaluationTool/jaccardParallelRectsOut.txt";
    std::string jaccardParallelImages="/Users/kyle/Documents/Thesis-EvaluationTool/jaccardParallelImagesOut.txt";
    
    
#if 1
    //read in the image files and store them in the image lists.
    tstart = dtime();
    getImgData(expertFileIn, keyImagesSerial);
    getImgData(traineeFileIn, test1ImagesSerial);
    tstop = dtime();
    ttime = tstop - tstart;
    
    JSFile.open(jaccardSerial, std::ofstream::out);
    if (!JSFile.is_open())
    {
        std::cout << "Error opening file" <<std::endl;
        return 1;
    }
    JSFile << "reading images completed in: " << ttime << " seconds." << std::endl;
    
    tstart = dtime();
    imageCompareSerial(test1ImagesSerial, keyImagesSerial);
    tstop = dtime();
    ttime = tstop - tstart;
    
    //std::cout << std::endl << std::endl;
    for ( keyImagesIterator= keyImagesSerial.begin(), i=1; keyImagesIterator!=keyImagesSerial.end(); ++keyImagesIterator, i++)
    {
        JSFile << "img " << i << ": " << (*keyImagesIterator)->getName() << " score: " << (*keyImagesIterator)->getNumMatches2() << " / " << (*keyImagesIterator)->getNumRects() << std::endl;
    }
    
    JSFile << "comparison using jaccard index completed in: " << ttime << " seconds" << std::endl;
    
#endif

#if 1
    //compare images using the rectangle parallel method
    tstart = dtime();
    getImgData(expertFileIn, keyImagesParallelR);
    getImgData(traineeFileIn, test1ImagesParallelR);
    tstop = dtime();
    ttime = tstop - tstart;
    JPRFile.open(jaccardParallelRects, std::ofstream::out);
    if (!JPRFile.is_open())
    {
        std::cout << "Error opening file" <<std::endl;
        return 1;
    }
    JPRFile << "reading images completed in: " << ttime << " seconds." << std::endl;
    
    std::vector<std::thread> threadVec;
    

    
    
    
    //in order to do parallel by images, need to put the imageList into a vector

    
    
    tstart = dtime();
    rectangleCompareParallel(test1ImagesParallelR, keyImagesParallelR);
    tstop = dtime();
    ttime = tstop - tstart;
    
    //std::cout << std::endl << std::endl;
    for ( keyImagesIterator= keyImagesParallelR.begin(), i=1; keyImagesIterator!=keyImagesParallelR.end(); ++keyImagesIterator, i++)
    {
        JPRFile << "img " << i << ": " << (*keyImagesIterator)->getName() << " score: " << (*keyImagesIterator)->getNumMatches2() << " / " << (*keyImagesIterator)->getNumRects() << std::endl;
    }
    JPRFile << "comparison using jaccard index in parallel(rects) completed in: " << ttime << " seconds" << std::endl;
    
#endif
    
    
#if 1
    //compare images using the images parallel method
    tstart = dtime();
    getImgData(expertFileIn, keyImagesParallelI);
    getImgData(traineeFileIn, test1ImagesParallelI);
    tstop = dtime();
    ttime = tstop - tstart;
    JPIFile.open(jaccardParallelImages, std::ofstream::out);
    if (!JPIFile.is_open())
    {
        std::cout << "Error opening file" <<std::endl;
        return 1;
    }
    JPIFile << "reading images completed in: " << ttime << " seconds." << std::endl;
    
    //convert list to vector for this method.
    keyImgVec.reserve(keyImagesParallelI.size());
    checkImgVec.reserve(test1ImagesParallelI.size());
    
    keyImgVec.insert(keyImgVec.end(),keyImagesParallelI.begin(),keyImagesParallelI.end());
    checkImgVec.insert(checkImgVec.end(), test1ImagesParallelI.begin(), test1ImagesParallelI.end());
    
    tstart = dtime();
    imageCompareParallelWrapper(checkImgVec, keyImgVec, NUM_THREADS);
    tstop = dtime();
    ttime = tstop - tstart;
    
    //std::cout << std::endl << std::endl;
    for ( keyImagesIterator= keyImagesParallelI.begin(), i=1; keyImagesIterator!=keyImagesParallelI.end(); ++keyImagesIterator, i++)
    {
        JPIFile << "img " << i << ": " << (*keyImagesIterator)->getName() << " score: " << (*keyImagesIterator)->getNumMatches2() << " / " << (*keyImagesIterator)->getNumRects() << std::endl;
    }
    JPIFile << "comparison using jaccard index in parallel(images) completed in: " << ttime << " seconds" << std::endl;
    
#endif
    
    std::cout << "success!" << std::endl;
    return 0;
}
