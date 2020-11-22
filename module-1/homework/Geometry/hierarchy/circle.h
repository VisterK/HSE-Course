#ifndef HIERARCHY_CIRCLE_H
#define HIERARCHY_CIRCLE_H

#include "ellipse.h"

class Circle : public Ellipse{
public:

    Circle(Point center, double radius);
    double radius();


    Point center;
    double r;

};
#endif