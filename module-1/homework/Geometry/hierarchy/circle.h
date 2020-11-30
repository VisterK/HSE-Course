#pragma once

#include "ellipse.h"

class Circle : public Ellipse{
public:

    Circle(Point center, double radius);
    double radius() const;

private:
    Point center;
    double r;

};