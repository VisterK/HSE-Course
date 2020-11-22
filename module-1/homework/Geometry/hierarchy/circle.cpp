#include "circle.h"
#include "point.h"

Circle::Circle(Point center,
               double radius) : Ellipse(center,center, radius * 2), r(radius){}

double Circle::radius(){
    return r;
}