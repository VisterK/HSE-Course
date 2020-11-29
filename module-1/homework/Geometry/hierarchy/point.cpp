#include "point.h"

Point::Point(double x_, double y_) : x(x_), y(y_){}


bool Point::operator==(const Point& rhs) const{
    return((std::fabs(x - rhs.x) < PI) && (std::fabs(y - rhs.y) < PI));
}

bool Point::operator!=(const Point& rhs) const{
    return(!(*this == rhs));
}

Point Point::operator+(const Point& rhs) const{
    return  Point(x + rhs.x, y + rhs.y);
}
Point Point::operator-(const Point& rhs) const{
    return Point(x - rhs.x, y - rhs.y);
}

Point Point::operator*(const double lambda) const{
    return Point(x * lambda, y * lambda);
}

double Point::distance(const Point& left, const Point& right){
    double x_coordinate = (left.x - right.x) * (left.x - right.x);
    double y_coordinate = (left.y - right.y) * (left.y - right.y);
    return sqrt(x_coordinate + y_coordinate);
}