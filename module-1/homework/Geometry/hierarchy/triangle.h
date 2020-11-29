#pragma once

#include "polygon.h"
#include "circle.h"

class Triangle : public Polygon{
public:

    Triangle(Point, Point, Point);

    Circle circumscribedCircle();
    Circle inscribedCircle();
};

