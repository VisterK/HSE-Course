

#include "point.h"
#include <cmath>
#include "extra.h"

Point::Point(double x_, double y_) : x(x_), y(y_){}


bool Point::operator==(const Point& rhs) const{
    if(x == rhs.x && y == rhs.y)
        return true;
    return false;
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