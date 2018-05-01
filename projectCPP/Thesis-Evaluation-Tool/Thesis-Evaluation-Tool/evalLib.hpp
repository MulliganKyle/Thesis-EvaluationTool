//
//  evalLib.hpp
//  Thesis-Evaluation-Tool
//
//  Created by Kyle Mulligan on 1/23/18.
//  Copyright © 2018 Kyle Mulligan. All rights reserved.
//

#ifndef evalLib_hpp
#define evalLib_hpp

#include <stdio.h>
#include <list>
#include <fstream>
#include <cmath>
#include <sys/time.h>
#include <thread>
#include <vector>
#include <mutex>


#include "rectangle.hpp"
#include "image.hpp"

#define CENTER_PERCENT_ERROR 0.5
#define AREA_PERCENT_ERROR 0.05



double dtime();

void getImgData(std::string, std::list<Image*>&);
void getImgDataParallel(std::string, std::list<Image*>&);

void compareImages(const std::list<Image*>&, const std::list<Image*>&);
void compareImages2(const std::list<Image*>&, const std::list<Image*>&);
void getRectScore(Image*, Rectangle*, std::list<Rectangle*>&);
void compareImagesParallel(const std::list<Image*>&, const std::list<Image*>&);
void compareImagesParallel2(const std::list<Image*>&, const std::list<Image*>&, int);
void getRectScore2(std::vector<Image*>, std::vector<Image*> , int, int);


#endif /* evalLib_hpp */
