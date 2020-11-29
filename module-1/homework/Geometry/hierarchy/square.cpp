#include "square.h"

Square::Square(Point A_, Point C_):Rectangle(A_,C_, 1){}

Circle Square::circumscribedCircle(){
    return Circle(Point((A + C) * 0.5), Point::distance(A,C) / 2.0);
}

Circle Square::inscribedCircle(){
    Point center = Point((A + C) * 0.5);
    double side = (Point::distance(A,C) / 2.0) / sqrt(2);
    Circle inscribed_circle = Circle(center,side / 2.0);
}