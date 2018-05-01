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

#define NUM_THREADS 4

int main(int argc, const char * argv[])
{
    
    std::ofstream JSFile;
    std::ofstream JPRFile;
    std::ofstream JPIFile;
    
        std::list<Image*>::const_iterator keyImagesIterator;
    std::list<Image*> keyImages;
    std::list<Image*> test1Images;
    
    double tstart, tstop, ttime;
    
    int i;
    

    
    std::string keyPath="/Users/kyle/Documents/Thesis-EvaluationTool/generate_data/KeyDataWithValTags.txt";
    std::string checkPath="/Users/kyle/Documents/Thesis-EvaluationTool/generate_data/extraData/out001.txt";
    
    std::string jaccardSerial="/Users/kyle/Documents/Thesis-EvaluationTool/jaccardSerialOut.txt";
    std::string jaccardParallelRects="/Users/kyle/Documents/Thesis-EvaluationTool/jaccardParallelRectsOut.txt";
    std::string jaccardParallelImages="/Users/kyle/Documents/Thesis-EvaluationTool/jaccardParallelImagesOut.txt";
    
    //read in the image files and store them in the image lists.
    tstart = dtime();
    getImgData(keyPath, keyImages);
    getImgData(checkPath, test1Images);
    tstop = dtime();
    ttime = tstop - tstart;
    
    
    //this section uses the old rectangle comparison method probably gonna delete this.
#if 0
    tstart = dtime();
    compareImages(keyImages,test1Images);
    tstop = dtime();
    ttime = tstop - tstart;
    
    std::cout << std::endl << std::endl;
    for ( keyImagesIterator= keyImages.begin(); keyImagesIterator!=keyImages.end(); ++keyImagesIterator)
    {
        std::cout << (*keyImagesIterator)->getName() << " score: " << (*keyImagesIterator)->getNumMatches() << " / " << (*keyImagesIterator)->getNumRects() << std::endl;
    }
    std::cout << "comparison using old method completed in: " << ttime << " seconds" << std::endl;
#endif
    
    
    //this section uses the new rectangle comparison method, jaccard index intersection/union
#if 0
    JSFile.open(jaccardSerial, std::ofstream::out);
    if (!JSFile.is_open())
    {
        std::cout << "Error opening file" <<std::endl;
        return 1;
    }
    JSFile << "reading images completed in: " << ttime << " seconds." << std::endl;

    tstart = dtime();
    compareImages2(keyImages,test1Images);
    tstop = dtime();
    ttime = tstop - tstart;
    
    std::cout << std::endl << std::endl;
    for ( keyImagesIterator= keyImages.begin(), i=1; keyImagesIterator!=keyImages.end(); ++keyImagesIterator, i++)
    {
        JSFile << "img " << i << ": " << (*keyImagesIterator)->getName() << " score: " << (*keyImagesIterator)->getNumMatches2() << " / " << (*keyImagesIterator)->getNumRects() << std::endl;
    }
    
    JSFile << "comparison using jaccard index completed in: " << ttime << " seconds" << std::endl;
#endif
    

    //compare images using the rectangle parallel method
#if 0
    JPRFile.open(jaccardParallelRects, std::ofstream::out);
    if (!JPRFile.is_open())
    {
        std::cout << "Error opening file" <<std::endl;
        return 1;
    }
    JPRFile << "reading images completed in: " << ttime << " seconds." << std::endl;

    tstart = dtime();
    compareImagesParallel(keyImages,test1Images);
    tstop = dtime();
    ttime = tstop - tstart;
    
    std::cout << std::endl << std::endl;
    for ( keyImagesIterator= keyImages.begin(), i=1; keyImagesIterator!=keyImages.end(); ++keyImagesIterator, i++)
    {
        JPRFile << "img " << i << ": " << (*keyImagesIterator)->getName() << " score: " << (*keyImagesIterator)->getNumMatches2() << " / " << (*keyImagesIterator)->getNumRects() << std::endl;
    }
    JPRFile << "comparison using jaccard index in parallel(rects) completed in: " << ttime << " seconds" << std::endl;
    
#endif
    
    //compare images using the images parallel method
#if 1
    JPIFile.open(jaccardParallelImages, std::ofstream::out);
    if (!JPIFile.is_open())
    {
        std::cout << "Error opening file" <<std::endl;
        return 1;
    }
    JPIFile << "reading images completed in: " << ttime << " seconds." << std::endl;

    
    
    
    tstart = dtime();
    compareImagesParallel2(keyImages,test1Images, NUM_THREADS);
    tstop = dtime();
    ttime = tstop - tstart;
    
    std::cout << std::endl << std::endl;
    for ( keyImagesIterator= keyImages.begin(), i=1; keyImagesIterator!=keyImages.end(); ++keyImagesIterator, i++)
    {
        JPIFile << "img " << i << ": " << (*keyImagesIterator)->getName() << " score: " << (*keyImagesIterator)->getNumMatches2() << " / " << (*keyImagesIterator)->getNumRects() << std::endl;
    }
    JPIFile << "comparison using jaccard index in parallel(images) completed in: " << ttime << " seconds" << std::endl;
    
#endif
    
    return 0;
}
