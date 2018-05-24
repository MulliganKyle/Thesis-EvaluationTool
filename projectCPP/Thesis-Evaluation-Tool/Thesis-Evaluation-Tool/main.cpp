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
    std::ofstream JSFFile;
    std::ofstream JPRFile;
    std::ofstream JPIFile;
    std::ofstream JPIRFile;

    
    std::list<Image*>::const_iterator keyImagesIterator;
    std::list<Image*> keyImagesSerial;
    std::list<Image*> test1ImagesSerial;
    
    std::list<Image*> keyImagesSerialF;
    std::list<Image*> test1ImagesSerialF;
    
    std::list<Image*> keyImagesParallelR;
    std::list<Image*> test1ImagesParallelR;
    
    std::list<Image*> keyImagesParallelI;
    std::list<Image*> test1ImagesParallelI;
    
    std::list<Image*> keyImagesParallelIR;
    std::list<Image*> test1ImagesParallelIR;
    
    std::vector<Image*> keyImgVec;
    std::vector<Image*> checkImgVec;
    
    Image* imagePTR;
    
    double tstart, tstop, ttime;
    double tstartA, tstopA, ttimeA;
    
    int i, j;
    

    
    std::string expertFileIn="/Users/kyle/Documents/Thesis-EvaluationTool/generate_data/moreTestData/expertDataExtended01.txt";
    std::string traineeFileIn="/Users/kyle/Documents/Thesis-EvaluationTool/generate_data/moreTestData/traineeDataExtended01.txt";
    
    std::string filesPath="/Users/kyle/Documents/Thesis-EvaluationTool/generate_data/extraData/";
    
    std::string expertFileInPath;
    std::string traineeFileInPath;
    std::string resultsFileOutPath;
    std::string traineeFileName;
    std::string resultsName;
    std::string reportFilePath;
    std::string reportFileName="report.txt";
    
    //std::string traineeFileIn="/Users/kyle/Documents/Thesis-EvaluationTool/generate_data/moreTestData/expertDataExtended01.txt";
    
    //std::string expertFileIn="/Users/kyle/Documents/Thesis-EvaluationTool/ImageFiles/key.txt";
    //std::string traineeFileIn="/Users/kyle/Documents/Thesis-EvaluationTool/ImageFiles/key.txt";
    
    //std::string expertFileIn="/Users/kyle/Documents/Thesis-EvaluationTool/expertFiles/extraData/out_001_001_Output_EZRA1-clean.txt";
    //std::string traineeFileIn="/Users/kyle/Documents/Thesis-EvaluationTool/expertFiles/extraData/out_002_001_Output_EZRA2-clean.txt";
    
    std::string jaccardSerial="/Users/kyle/Documents/Thesis-EvaluationTool/jaccardSerialOut.txt";
    std::string jaccardParallelRects="/Users/kyle/Documents/Thesis-EvaluationTool/jaccardParallelRectsOut.txt";
    std::string jaccardParallelImages="/Users/kyle/Documents/Thesis-EvaluationTool/jaccardParallelImagesOut.txt";
    
    /*******************************************************************************/
    /*******************************************************************************/
    /**                                                                           **/
    /**                                                                           **/
    /**                             Serial test                                   **/
    /**                                                                           **/
    /**                                                                           **/
    /*******************************************************************************/
    /*******************************************************************************/
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
        JSFile << "img " << i << ": " << (*keyImagesIterator)->getName() << " score: " << (*keyImagesIterator)->getNumMatches() << " / " << (*keyImagesIterator)->getNumRects() << std::endl;
    }
    
    JSFile << "comparison using jaccard index completed in: " << ttime << " seconds" << std::endl;
    
#endif

    
    /*******************************************************************************/
    /*******************************************************************************/
    /**                                                                           **/
    /**                                                                           **/
    /**                             Parallel test                                 **/
    /**                         Images are parallel                               **/
    /**                                                                           **/
    /*******************************************************************************/
    /*******************************************************************************/
    
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
        JPRFile << "img " << i << ": " << (*keyImagesIterator)->getName() << " score: " << (*keyImagesIterator)->getNumMatches() << " / " << (*keyImagesIterator)->getNumRects() << std::endl;
    }
    JPRFile << "comparison using jaccard index in parallel(rects) completed in: " << ttime << " seconds" << std::endl;
    
#endif
    
    /*******************************************************************************/
    /*******************************************************************************/
    /**                                                                           **/
    /**                                                                           **/
    /**                             Parallel test                                 **/
    /**                       Rectangles are parallel                             **/
    /**                                                                           **/
    /*******************************************************************************/
    /*******************************************************************************/
    
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
        JPIFile << "img " << i << ": " << (*keyImagesIterator)->getName() << " score: " << (*keyImagesIterator)->getNumMatches() << " / " << (*keyImagesIterator)->getNumRects() << std::endl;
    }
    JPIFile << "comparison using jaccard index in parallel(images) completed in: " << ttime << " seconds" << std::endl;
    
#endif
    
    
    /*******************************************************************************/
    /*******************************************************************************/
    /**                                                                           **/
    /**                                                                           **/
    /**                              Serial test                                  **/
    /**                            several files                                  **/
    /**                                                                           **/
    /*******************************************************************************/
    /*******************************************************************************/
    
#if 1
    ttimeA=0.0;
    tstart = dtime();
    tstartA = dtime();
    expertFileInPath=filesPath+"expert.txt";
    getImgData(expertFileInPath, keyImagesSerialF);
    tstopA = dtime();
    ttimeA = ttimeA + (tstopA - tstartA);
    
    for (j = 1; j<=10; j++)
    {
        
        if (j<10)
        {
            traineeFileName ="out00"+std::to_string(j)+".txt";
            resultsName="results00"+std::to_string(j)+".txt";
        }
        else if (j < 100)
        {
            traineeFileName ="out0"+std::to_string(j)+".txt";
            resultsName="results0"+std::to_string(j)+".txt";
        }
        else
        {
            traineeFileName ="out"+std::to_string(j)+".txt";
            resultsName="results"+std::to_string(j)+".txt";
        }
        
        traineeFileInPath = filesPath+traineeFileName;
        resultsFileOutPath = filesPath+resultsName;
        
        tstartA = dtime();
        getImgData(traineeFileInPath, test1ImagesSerialF);
        tstopA = dtime();
        ttimeA = ttimeA + (tstopA - tstartA);
        
        
        JSFFile.open(resultsFileOutPath, std::ofstream::out);
        if (!JSFFile.is_open())
        {
            std::cout << "Error opening file" <<std::endl;
            return 1;
        }
        
        tstartA = dtime();
        //compare images
        imageCompareSerial(test1ImagesSerialF, keyImagesSerialF);
        tstopA = dtime();
        ttimeA = ttimeA + (tstopA - tstartA);
        
        //output data to file
        for ( keyImagesIterator= keyImagesSerialF.begin(), i=1; keyImagesIterator!=keyImagesSerialF.end(); ++keyImagesIterator, i++)
        {
            JSFFile << "img " << i << ": " << (*keyImagesIterator)->getName() << " score: " << (*keyImagesIterator)->getNumMatches() << " / " << (*keyImagesIterator)->getNumRects() << std::endl;
        }
        
        JSFFile << std::endl << std::endl << "Comparison completed successfully using jaccard index." << std::endl;
        
        JSFFile.close();

        tstartA = dtime();
        for ( keyImagesIterator= keyImagesSerialF.begin(); keyImagesIterator!=keyImagesSerialF.end(); ++keyImagesIterator)
        {
            (*keyImagesIterator)->clean();
        }
        while ( !test1ImagesSerialF.empty() )
        {
            imagePTR = test1ImagesSerialF.back();
            test1ImagesSerialF.pop_back();
            imagePTR->~Image();
        }
        tstopA = dtime();
        ttimeA = ttimeA + (tstopA - tstartA);
        
    }
    tstop = dtime();
    ttime = tstop - tstart;
    
    reportFilePath=filesPath+reportFileName;
    JSFFile.open(reportFilePath, std::ofstream::out);
    if (!JSFFile.is_open())
    {
        std::cout << "Error opening file" <<std::endl;
        return 1;
    }
    JSFFile << "Comparison of " << j-1 << " files completed successfully using jaccard index." << std::endl;
    JSFFile << "Output provided in " << ttime << " seconds." << std::endl;
    JSFFile << "Comparison not including file output completed in " << ttimeA << " seconds." <<std::endl;
    
    
    
#endif
    
    
    std::cout << "success!" << std::endl;
    return 0;
}
