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

#include "rectangle.hpp"
#include "image.hpp"





void getImgData(std::string, std::list<Image*>&);

void compareImages(const std::list<Image*>&, const std::list<Image*>&);

#endif /* evalLib_hpp */
