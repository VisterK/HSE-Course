#ifndef HIERARCHY_RECTANGLE_H
#define HIERARCHY_RECTANGLE_H

#include "point.h"
#include "line.h"
#include "polygon.h"

class Rectangle : public Polygon{
public:
    Rectangle(Point top_, Point bottom_, double ratio_);

    Point center();
    std::pair<Line,Line> diagonals();

    Point A;
    Point C;
    double ratio;

};

#endif