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
#define NUM_FILES 201

int main(int argc, const char * argv[])
{
    
    std::ofstream outputFile;
    
    std::list<Image*>::const_iterator imagesIterator;
    std::list<Image*> expertImages;
    std::list<Image*> traineeImages;
    
    std::vector<std::thread> threadVec;

    
    std::vector<Image*> expertImagesVector;
    std::vector<Image*> traineeImagesVector;
    
    Image* imagePTR;
    
    double tstart, tstop, ttime;
    double tstartA, tstopA, ttimeA;
    
    int i, j, threadCount;
    

    
    std::string expertFileIn="/Users/kyle/Documents/Thesis-EvaluationTool/generate_data/moreTestData/expertDataExtended01.txt";
    std::string traineeFileIn="/Users/kyle/Documents/Thesis-EvaluationTool/generate_data/moreTestData/traineeDataExtended01.txt";
    
    std::string filesPath="/Users/kyle/Documents/Thesis-EvaluationTool/generate_data/extraData0";
    
    std::string expertFileInPath;
    std::string traineeFileInPath;
    std::string resultsFileOutPath;
    std::string traineeFileName;
    std::string resultsName;
    std::string reportFilePath;
    std::string reportFileName="AAA_report.txt";
    
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
    getImgData(expertFileIn, expertImages);
    getImgData(traineeFileIn, traineeImages);
    tstop = dtime();
    ttime = tstop - tstart;
    
    outputFile.open(jaccardSerial, std::ofstream::out);
    if (!outputFile.is_open())
    {
        std::cout << "Error opening file" <<std::endl;
        return 1;
    }
    outputFile << "reading images completed in: " << ttime << " seconds." << std::endl;
    
    tstart = dtime();
    imageCompareSerial(traineeImages, expertImages);
    tstop = dtime();
    ttime = tstop - tstart;
    
    //std::cout << std::endl << std::endl;
    for ( imagesIterator= expertImages.begin(), i=1; imagesIterator!=expertImages.end(); ++imagesIterator, i++)
    {
        outputFile << "img " << i << ": " << (*imagesIterator)->getName() << " score: " << (*imagesIterator)->getNumMatches() << " / " << (*imagesIterator)->getNumRects() << std::endl;
    }
    
    outputFile << "comparison using jaccard index completed in: " << ttime << " seconds" << std::endl;

    outputFile.close();
    
#endif
//delete all images from the two lists before next test
    while ( !expertImages.empty() )
    {
        imagePTR = expertImages.back();
        expertImages.pop_back();
        imagePTR->~Image();
    }
    while ( !traineeImages.empty() )
    {
        imagePTR = traineeImages.back();
        traineeImages.pop_back();
        imagePTR->~Image();
    }
    
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
    //compare images using the rectangle parallel method
    tstart = dtime();
    getImgData(expertFileIn, expertImages);
    getImgData(traineeFileIn, traineeImages);
    tstop = dtime();
    ttime = tstop - tstart;
    outputFile.open(jaccardParallelRects, std::ofstream::out);
    if (!outputFile.is_open())
    {
        std::cout << "Error opening file" <<std::endl;
        return 1;
    }
    outputFile << "reading images completed in: " << ttime << " seconds." << std::endl;
    

    
    
    tstart = dtime();
    rectangleCompareParallel(traineeImages, expertImages);
    tstop = dtime();
    ttime = tstop - tstart;
    
    //std::cout << std::endl << std::endl;
    for ( imagesIterator= expertImages.begin(), i=1; imagesIterator!=expertImages.end(); ++imagesIterator, i++)
    {
        outputFile << "img " << i << ": " << (*imagesIterator)->getName() << " score: " << (*imagesIterator)->getNumMatches() << " / " << (*imagesIterator)->getNumRects() << std::endl;
    }
    outputFile << "comparison using jaccard index in parallel(rects) completed in: " << ttime << " seconds" << std::endl;
    outputFile.close();
    
#endif
    //delete all images from the two lists before next test
    while ( !expertImages.empty() )
    {
        imagePTR = expertImages.back();
        expertImages.pop_back();
        imagePTR->~Image();
    }
    while ( !traineeImages.empty() )
    {
        imagePTR = traineeImages.back();
        traineeImages.pop_back();
        imagePTR->~Image();
    }
    
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
    //compare images using the images parallel method
    tstart = dtime();
    getImgData(expertFileIn, expertImages);
    getImgData(traineeFileIn, traineeImages);
    tstop = dtime();
    ttime = tstop - tstart;
    outputFile.open(jaccardParallelImages, std::ofstream::out);
    if (!outputFile.is_open())
    {
        std::cout << "Error opening file" <<std::endl;
        return 1;
    }
    outputFile << "reading images completed in: " << ttime << " seconds." << std::endl;
    
    //convert list to vector for this method.
    expertImagesVector.reserve(expertImages.size());
    traineeImagesVector.reserve(traineeImages.size());
    
    expertImagesVector.insert(expertImagesVector.end(),expertImages.begin(),expertImages.end());
    traineeImagesVector.insert(traineeImagesVector.end(), traineeImages.begin(), traineeImages.end());
    
    tstart = dtime();
    imageCompareParallelWrapper(traineeImagesVector, expertImagesVector, NUM_THREADS);
    tstop = dtime();
    ttime = tstop - tstart;
    
    //std::cout << std::endl << std::endl;
    for ( imagesIterator= expertImages.begin(), i=1; imagesIterator!=expertImages.end(); ++imagesIterator, i++)
    {
        outputFile << "img " << i << ": " << (*imagesIterator)->getName() << " score: " << (*imagesIterator)->getNumMatches() << " / " << (*imagesIterator)->getNumRects() << std::endl;
    }
    outputFile << "comparison using jaccard index in parallel(images) completed in: " << ttime << " seconds" << std::endl;
    
    outputFile.close();
    
#endif
    //delete all images from the two lists before next test
    while ( !expertImages.empty() )
    {
        imagePTR = expertImages.back();
        expertImages.pop_back();
        imagePTR->~Image();
    }
    while ( !traineeImages.empty() )
    {
        imagePTR = traineeImages.back();
        traineeImages.pop_back();
        imagePTR->~Image();
    }
    
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
    expertFileInPath=filesPath+"1/"+"expert.txt";
    getImgData(expertFileInPath, expertImages);
    tstopA = dtime();
    ttimeA = ttimeA + (tstopA - tstartA);
    
    for (j = 0; j<NUM_FILES; j++)
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
        
        traineeFileInPath = filesPath+"1/"+traineeFileName;
        resultsFileOutPath = filesPath+"1/"+resultsName;
        
        tstartA = dtime();
        getImgData(traineeFileInPath, traineeImages);
        tstopA = dtime();
        ttimeA = ttimeA + (tstopA - tstartA);
        
        
        outputFile.open(resultsFileOutPath, std::ofstream::out);
        if (!outputFile.is_open())
        {
            std::cout << "Error opening file" <<std::endl;
            return 1;
        }
        
        tstartA = dtime();
        //compare images
        imageCompareSerial(traineeImages, expertImages);
        tstopA = dtime();
        ttimeA = ttimeA + (tstopA - tstartA);
        
        //output data to file
        for ( imagesIterator= expertImages.begin(), i=1; imagesIterator!=expertImages.end(); ++imagesIterator, i++)
        {
            outputFile << "img " << i << ": " << (*imagesIterator)->getName() << " score: " << (*imagesIterator)->getNumMatches() << " / " << (*imagesIterator)->getNumRects() << std::endl;
        }
        
        outputFile << std::endl << std::endl << "Comparison completed successfully using jaccard index." << std::endl;
        
        outputFile.close();

        //clean the expert images and delete the trainee images
        tstartA = dtime();
        for ( imagesIterator= expertImages.begin(); imagesIterator!=expertImages.end(); ++imagesIterator)
        {
            (*imagesIterator)->clean();
        }
        while ( !traineeImages.empty() )
        {
            imagePTR = traineeImages.back();
            traineeImages.pop_back();
            imagePTR->~Image();
        }
        tstopA = dtime();
        ttimeA = ttimeA + (tstopA - tstartA);
        
    }
    tstop = dtime();
    ttime = tstop - tstart;
    
    //output the report
    reportFilePath=filesPath+"1/"+reportFileName;
    outputFile.open(reportFilePath, std::ofstream::out);
    if (!outputFile.is_open())
    {
        std::cout << "Error opening file" <<std::endl;
        return 1;
    }
    outputFile << "Comparison of " << NUM_FILES << " files completed successfully using jaccard index." << std::endl;
    outputFile << "Output provided in " << ttime << " seconds." << std::endl;
    outputFile << "Comparison not including file output completed in " << ttimeA << " seconds." <<std::endl;
    
    outputFile.close();
    
#endif
    //delete all images from the two lists before next test
    while ( !expertImages.empty() )
    {
        imagePTR = expertImages.back();
        expertImages.pop_back();
        imagePTR->~Image();
    }
    while ( !traineeImages.empty() )
    {
        imagePTR = traineeImages.back();
        traineeImages.pop_back();
        imagePTR->~Image();
    }
    
    /*******************************************************************************/
    /*******************************************************************************/
    /**                                                                           **/
    /**                                                                           **/
    /**                         Parallel Image test                               **/
    /**                            several files                                  **/
    /**                         vvvvvvvvvvvvvvvvvvv                               **/
    /*******************************************************************************/
    /*******************************************************************************/
    
    //parallel image test
#if 1
    ttimeA=0.0;
    tstart = dtime();
    tstartA = dtime();
    expertFileInPath=filesPath+"2/"+"expert.txt";
    getImgData(expertFileInPath, expertImages);
    tstopA = dtime();
    ttimeA = ttimeA + (tstopA - tstartA);
    
    for (j = 0; j<NUM_FILES; j++)
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
        
        traineeFileInPath = filesPath+"2/"+traineeFileName;
        resultsFileOutPath = filesPath+"2/"+resultsName;
        
        tstartA = dtime();
        getImgData(traineeFileInPath, traineeImages);
        tstopA = dtime();
        ttimeA = ttimeA + (tstopA - tstartA);
        
        
        outputFile.open(resultsFileOutPath, std::ofstream::out);
        if (!outputFile.is_open())
        {
            std::cout << "Error opening file" <<std::endl;
            return 1;
        }
        
        //convert list to vector for this method.
        expertImagesVector.reserve(expertImages.size());
        traineeImagesVector.reserve(traineeImages.size());
        
        expertImagesVector.insert(expertImagesVector.end(),expertImages.begin(),expertImages.end());
        traineeImagesVector.insert(traineeImagesVector.end(), traineeImages.begin(), traineeImages.end());

        
        tstartA = dtime();
        //compare images
        imageCompareParallelWrapper(traineeImagesVector, expertImagesVector, NUM_THREADS);
        tstopA = dtime();
        ttimeA = ttimeA + (tstopA - tstartA);
        
        //output data to file
        for ( imagesIterator= expertImages.begin(), i=1; imagesIterator!=expertImages.end(); ++imagesIterator, i++)
        {
            outputFile << "img " << i << ": " << (*imagesIterator)->getName() << " score: " << (*imagesIterator)->getNumMatches() << " / " << (*imagesIterator)->getNumRects() << std::endl;
        }
        
        outputFile << std::endl << std::endl << "Comparison completed successfully using jaccard index." << std::endl;
        
        outputFile.close();
        
        //clean the expert images and delete the trainee images
        tstartA = dtime();
        for ( imagesIterator= expertImages.begin(); imagesIterator!=expertImages.end(); ++imagesIterator)
        {
            (*imagesIterator)->clean();
        }
        while ( !traineeImages.empty() )
        {
            imagePTR = traineeImages.back();
            traineeImages.pop_back();
            imagePTR->~Image();
        }
        
        traineeImagesVector.clear();
        expertImagesVector.clear();
        
        tstopA = dtime();
        ttimeA = ttimeA + (tstopA - tstartA);
        
    }
    tstop = dtime();
    ttime = tstop - tstart;
    
    //output the report
    reportFilePath=filesPath+"2/"+reportFileName;
    outputFile.open(reportFilePath, std::ofstream::out);
    if (!outputFile.is_open())
    {
        std::cout << "Error opening file" <<std::endl;
        return 1;
    }
    outputFile << "Comparison of " << NUM_FILES << " files completed successfully using jaccard index for parallel images, using " << NUM_THREADS << "threads." << std::endl;
    outputFile << "Output provided in " << ttime << " seconds." << std::endl;
    outputFile << "Comparison not including file output and not including time to copy to vector completed in " << ttimeA << " seconds." <<std::endl;
    outputFile << "Comparison does not include the vector copy because this method could be done without this copy by having the file read go directly to a vector instead. This was not implemented here because a list was sufficient for the other parallel methods." << std::endl;
    outputFile.close();

#endif
    while ( !expertImages.empty() )
    {
        imagePTR = expertImages.back();
        expertImages.pop_back();
        imagePTR->~Image();
    }
    while ( !traineeImages.empty() )
    {
        imagePTR = traineeImages.back();
        traineeImages.pop_back();
        imagePTR->~Image();
    }
    
    /*******************************************************************************/
    /*******************************************************************************/
    /**                                                                           **/
    /**                                                                           **/
    /**                       Parallel rectangle test                             **/
    /**                            several files                                  **/
    /**                         vvvvvvvvvvvvvvvvvvv                               **/
    /*******************************************************************************/
    /*******************************************************************************/
    
    //delete all images in the trainee and expert image list before next test

#if 1
    ttimeA=0.0;
    tstart = dtime();
    tstartA = dtime();
    expertFileInPath=filesPath+"3/"+"expert.txt";
    getImgData(expertFileInPath, expertImages);
    tstopA = dtime();
    ttimeA = ttimeA + (tstopA - tstartA);
    
    for (j = 0; j<NUM_FILES; j++)
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
        
        traineeFileInPath = filesPath+"3/"+traineeFileName;
        resultsFileOutPath = filesPath+"3/"+resultsName;
        
        tstartA = dtime();
        getImgData(traineeFileInPath, traineeImages);
        tstopA = dtime();
        ttimeA = ttimeA + (tstopA - tstartA);
        
        
        outputFile.open(resultsFileOutPath, std::ofstream::out);
        if (!outputFile.is_open())
        {
            std::cout << "Error opening file" <<std::endl;
            return 1;
        }
        
        tstartA = dtime();
        //compare images
        rectangleCompareParallel(traineeImages, expertImages);
        tstopA = dtime();
        ttimeA = ttimeA + (tstopA - tstartA);
        
        //output data to file
        for ( imagesIterator= expertImages.begin(), i=1; imagesIterator!=expertImages.end(); ++imagesIterator, i++)
        {
            outputFile << "img " << i << ": " << (*imagesIterator)->getName() << " score: " << (*imagesIterator)->getNumMatches() << " / " << (*imagesIterator)->getNumRects() << std::endl;
        }
        
        outputFile << std::endl << std::endl << "Comparison completed successfully using jaccard index." << std::endl;
        
        outputFile.close();
        
        tstartA = dtime();
        for ( imagesIterator= expertImages.begin(); imagesIterator!=expertImages.end(); ++imagesIterator)
        {
            (*imagesIterator)->clean();
        }
        while ( !traineeImages.empty() )
        {
            imagePTR = traineeImages.back();
            traineeImages.pop_back();
            imagePTR->~Image();
        }
        tstopA = dtime();
        ttimeA = ttimeA + (tstopA - tstartA);
        
    }
    tstop = dtime();
    ttime = tstop - tstart;
    
    //output the report
    reportFilePath=filesPath+"3/"+reportFileName;
    outputFile.open(reportFilePath, std::ofstream::out);
    if (!outputFile.is_open())
    {
        std::cout << "Error opening file" <<std::endl;
        return 1;
    }
    outputFile << "Comparison of " << NUM_FILES << " files completed successfully using jaccard index for parallel rectangles, using " << NUM_THREADS << "threads." << std::endl;
    outputFile << "Output provided in " << ttime << " seconds." << std::endl;
    outputFile << "Comparison not including file output completed in " << ttimeA << " seconds." <<std::endl;
    outputFile.close();

#endif
    
    while ( !expertImages.empty() )
    {
        imagePTR = expertImages.back();
        expertImages.pop_back();
        imagePTR->~Image();
    }
    while ( !traineeImages.empty() )
    {
        imagePTR = traineeImages.back();
        traineeImages.pop_back();
        imagePTR->~Image();
    }
    
    /*******************************************************************************/
    /*******************************************************************************/
    /**                                                                           **/
    /**                                                                           **/
    /**                         Parallel Files test                               **/
    /**                            several files                                  **/
    /**                         vvvvvvvvvvvvvvvvvvv                               **/
    /*******************************************************************************/
    /*******************************************************************************/
    
#if 1
    tstart = dtime();
    for (threadCount=0; threadCount< NUM_THREADS; threadCount++)
    {
        threadVec.push_back(std::thread(multiFileTest, filesPath, threadCount, NUM_THREADS, NUM_FILES));
    }
    
    for ( threadCount=0; threadCount < NUM_THREADS; ++threadCount)
    {
        (threadVec.back()).join();
        threadVec.pop_back();
    }
    tstop = dtime();
    ttime = tstop - tstart;
    
    //output the report
    reportFilePath=filesPath+"4/"+reportFileName;
    outputFile.open(reportFilePath, std::ofstream::out);
    if (!outputFile.is_open())
    {
        std::cout << "Error opening file" <<std::endl;
        return 1;
    }
    outputFile << "Comparison of " << NUM_FILES << " files completed successfully using jaccard index for parallel files, using " << NUM_THREADS << "threads." << std::endl;
    outputFile << "Output provided in " << ttime << " seconds." << std::endl;
    
    outputFile.close();
    
#endif
    
    std::cout << "success!" << std::endl;
    return 0;
}
