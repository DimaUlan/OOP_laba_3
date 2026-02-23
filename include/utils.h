#ifndef UTILS_H
#define UTILS_H

#include "Figure.h"
#include <iostream>

inline bool readPoint(std::istream& is, Point& p) {
    is >> p.x >> p.y;
    return !is.fail();
}

#endif