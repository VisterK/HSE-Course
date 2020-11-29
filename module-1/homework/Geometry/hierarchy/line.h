#pragma once

#include "point.h"

struct Line{

    Line() = default;
    Line(Point A_, Point B_);
    Line(double, double, double);

    bool operator ==(const Line& rhs) const;
    bool operator !=(const Line& rhs) const;

    double distToPoint(const Point point) const;

    double A;
    double B;
    double C;

};
