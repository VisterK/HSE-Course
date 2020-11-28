#pragma once

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
