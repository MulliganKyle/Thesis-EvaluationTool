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
    std::list<Image*>::const_iterator keyImagesIterator;
    
    std::string keyPath="/Users/kyle/Documents/Thesis-EvaluationTool/ImageFiles/key.txt";
    std::string checkPath="/Users/kyle/Documents/Thesis-EvaluationTool/ImageFiles/test1.txt";
    
    std::list<Image*> keyImages;
    std::list<Image*> test1Images;
    
    getImgData(keyPath, keyImages);
    getImgData(checkPath, test1Images);
    
    compareImages(keyImages,test1Images);
    
    //std::cout << keyImages.front()->getName() << std::endl;
    
    for ( keyImagesIterator= keyImages.begin(); keyImagesIterator!=keyImages.end(); ++keyImagesIterator)
    {
        std::cout << (*keyImagesIterator)->getName() << " score: " << (*keyImagesIterator)->getNumMatches() << " / " << (*keyImagesIterator)->getNumRects() << std::endl;
    }
    
    return 0;
}
