#include "line.h"

Line::Line(Point A_, Point B_){
    A = A_.y - B_.y;
    B = B_.x - A_.y;
    C = A_.x * B_.y - B_.x * A_.y;
}

Line::Line(double A_, double B_, double C_): A(A_), B(B_), C(C_){}

bool Line::operator ==(const Line& rhs) const{
    return(A == rhs.A && B == rhs.B);
}

bool Line::operator !=(const Line& rhs) const{
    return !(*this == rhs);
}

double Line::distToPoint(const Point& point) const{
    return (std::fabs(A * point.x + B * point.y + C))/(sqrt(A * A + B * B));
}
