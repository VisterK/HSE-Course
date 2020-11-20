#include "line.h"
#include <cmath>

Line::Line(Point A_, Point B_){
    A = A_.y - B_.y;
    B = B_.x - A_.y;
    C = A_.x * B_.y - B_.x * A_.y;
}

bool Line::operator ==(const Line& rhs) const{
    return(A == rhs.A && B == rhs.B);
}
bool Line::operator !=(const Line& rhs) const{
    return !(*this == rhs);
}

double Line::distToPoint(const Point point) const{
    return (abs(A * point.x + B * point.y + C))/(sqrt(A * A + B * B));
}