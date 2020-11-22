#ifndef HIERARCHY_SQUARE_H
#define HIERARCHY_SQUARE_H

#include "point.h"
#include "polygon.h"
#include "rectangle.h"
#include "circle.h"

class Square : public Rectangle{
public:
    Square(Point A_, Point C_);

    Circle circumscribedCircle();
    Circle inscribedCircle();

    Point A;
    Point C;
};

#endif