//
//  compareLib.hpp
//  Thesis-Evaluation-Tool
//
//  Created by Kyle Mulligan on 5/9/18.
//  Copyright © 2018 Kyle Mulligan. All rights reserved.
//

#ifndef compareLib_hpp
#define compareLib_hpp

#include <stdio.h>
#include <list>
#include <fstream>
#include <cmath>
#include <sys/time.h>
#include <thread>
#include <vector>
#include <mutex>

#include "evalLib.hpp"
#include "rectangle.hpp"
#include "image.hpp"


void imageCompareSerial(std::list<Image*>, std::list<Image*>);
void imageCompareSerialExperts(std::list<Image*>, std::list<Image*>);
void rectangleCompareSerial( Image*, Image*);
void traineeRectangleCompare( Image*, Rectangle*);

void imageCompareParallelWrapper(std::vector<Image*>, std::vector<Image*>, int);
void imageCompareParallel(std::vector<Image*>, std::vector<Image*>, int, int);

void rectangleCompareParallel(std::list<Image*>, std::list<Image*>);

void multiFileTest(std::string, int, int, int);

//void imageCompareSerialRectangleParallel(std::list<Image*>, std::list<Image*>);
//void imageRectangleCompareParallel(std::list<Image*>, std::list<Image*>);



#endif /* compareLib_hpp */
