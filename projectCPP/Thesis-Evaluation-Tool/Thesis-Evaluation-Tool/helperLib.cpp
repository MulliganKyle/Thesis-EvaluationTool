//
//  helperLib.cpp
//  Thesis-Evaluation-Tool
//
//  Created by Kyle Mulligan on 1/25/18.
//  Copyright © 2018 Kyle Mulligan. All rights reserved.
//

#include "helperLib.hpp"


//compares two rectangles and outputs which is closer to the top left of image. currently not used.
bool compareRec( Rectangle *first, Rectangle *second)
{
    if ( first->getX0() == second->getX0() )
    {
        if ( first->getY0() <= second->getY0() )
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else if ( first->getX0() < second->getX0() )
    {
        return true;
    }
    else
    {
        return false;
    }
}
