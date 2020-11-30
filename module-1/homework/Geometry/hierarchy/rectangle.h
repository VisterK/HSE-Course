#pragma once

#include "polygon.h"

class Rectangle : public Polygon{
public:
    Rectangle(Point A_, Point C_, double ratio_);

    Point center();
    std::pair<Line,Line> diagonals();

protected:
    Point A;
    Point C;
    double ratio;

};
