#include "circle.h"
#include "point.h"

Circle::Circle(Point center_,
               double radius) : Ellipse(center_,center_, radius * 2), r(radius), center(center_){}

double Circle::radius() const{
    return r;
}