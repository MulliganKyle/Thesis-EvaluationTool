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

int main(int argc, const char * argv[])
{
    double tstart, tstop, ttime;
    
    std::list<Image*>::const_iterator keyImagesIterator;
    
    std::string keyPath="/Users/kyle/Documents/Thesis-EvaluationTool/generate_data/KeyDataWithValTags.txt";
    std::string checkPath="/Users/kyle/Documents/Thesis-EvaluationTool/generate_data/extraData/out001.txt";
    
    std::list<Image*> keyImages;
    std::list<Image*> test1Images;
    tstart = dtime();
    getImgData(keyPath, keyImages);
    getImgData(checkPath, test1Images);
    tstop = dtime();
    ttime = tstop - tstart;
    
    std::cout << "reading images completed in: " << ttime << " seconds." << std::endl;
 
    
    //this section uses the old rectangle comparison method
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
    tstart = dtime();
    compareImages2(keyImages,test1Images);
    tstop = dtime();
    ttime = tstop - tstart;
    
    std::cout << std::endl << std::endl;
    for ( keyImagesIterator= keyImages.begin(); keyImagesIterator!=keyImages.end(); ++keyImagesIterator)
    {
        std::cout << (*keyImagesIterator)->getName() << " score: " << (*keyImagesIterator)->getNumMatches2() << " / " << (*keyImagesIterator)->getNumRects() << std::endl;
    }
    
    std::cout << "comparison using jaccard index completed in: " << ttime << " seconds" << std::endl;
#endif
    
    
    //this section will hold the new parallel comparison method
#if 1
    tstart = dtime();
    compareImagesParallel(keyImages,test1Images);
    tstop = dtime();
    ttime = tstop - tstart;
    
    std::cout << std::endl << std::endl;
    for ( keyImagesIterator= keyImages.begin(); keyImagesIterator!=keyImages.end(); ++keyImagesIterator)
    {
        std::cout << (*keyImagesIterator)->getName() << " score: " << (*keyImagesIterator)->getNumMatches2() << " / " << (*keyImagesIterator)->getNumRects() << std::endl;
    }
    std::cout << "comparison using jaccard index in parallel completed in: " << ttime << " seconds" << std::endl;
    
#endif
    
    return 0;
}
