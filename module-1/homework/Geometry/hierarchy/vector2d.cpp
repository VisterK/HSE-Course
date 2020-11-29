#include "vector2d.h"
#include <cmath>


vector2d::vector2d(): x(0), y(0){}
vector2d::vector2d(double x_, double y_) : x(x_),y(y_){}
vector2d::vector2d(Point A, Point B){
    x = A.x - B.x;
    y = A.y - B.y;
}

double vector2d::operator^(const vector2d& other) const{
    return(x * other.y - y * other.x);
}
double vector2d::operator*(const vector2d& other) const{
    return(x * other.x + y * other.y);
}
vector2d vector2d::operator*(const double lambda) const{
    return vector2d(x * lambda, y * lambda);
}

vector2d vector2d::operator+(const vector2d& other) const{
    vector2d answer = vector2d(x + other.x, y + other.y);
    return answer;
}

double vector2d::getLength() const{
    return (sqrt(x * x + y * y));
}
vector2d vector2d::normal(Line p) {
    return vector2d(p.A, p.B);
}
double vector2d::getAngle(vector2d& left, vector2d& right){
    double angle = (left*right) / (left.getLength() * right.getLength());
    angle = angle * PI / 180.0;
    angle = std::acos(angle);
    return angle;
}