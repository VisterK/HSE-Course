#ifndef HIERARCHY_EXTRA_H
#define HIERARCHY_EXTRA_H

#include "point.h"
#include <cmath>
#include <vector2d.h>

namespace extra{

    double EPS = 1e-6;
    double PI = 3.1415926;

    bool isEqual(double lhs, double rhs){
        return (std::abs(lhs - rhs) < EPS);
    }
    bool isEqual(const Point& lhs, const Point& rhs){
        bool x = extra::isEqual(lhs.x, rhs.x);
        bool y = extra::isEqual(lhs.y, rhs.y);
        return(x && y);
    }
    bool isNotEqual(double lhs, double rhs){
        return (!isEqual(lhs,rhs));
    }
    bool isGreater(double lhs, double rhs){
        return(lhs - rhs > EPS);
    }
    bool isLess(double lhs, double rhs){
        return(!(isEqual(lhs,rhs) || isGreater(lhs,rhs)));
    }
    double distance(const Point& left, const Point& right){
        double x_coordinate = (left.x - right.x) * (left.x - right.x);
        double y_coordinate = (left.y - right.y) * (left.y - right.y);
        return sqrt(x_coordinate + y_coordinate);
    }
    double getAngel(const vector2d& left, const vector2d& right){
        return (left*right) / (left.getLength() * right.getLength());
    }
    double toRad(const double& angle){
        return(angle * PI / 180.0);
    }
}
#endif