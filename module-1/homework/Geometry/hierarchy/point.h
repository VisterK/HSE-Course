#pragma once

#include <cmath>
#include "constants.h"

struct Point{


    Point() = default;
    Point(double, double);

    bool operator==(const Point& rhs) const;
    bool operator!=(const Point& rhs) const;

    Point operator+(const Point& rhs) const;
    Point operator-(const Point& rhs) const;
    Point operator*(const double& lambda) const;

    static double distance(const Point& left, const Point& right);

    double x;
    double y;
};
