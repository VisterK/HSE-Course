#pragma once

#include "ellipse.h"

class Circle : public Ellipse{
public:

    Circle(Point center, double radius);
    double radius();


    Point center;
    double r;

};