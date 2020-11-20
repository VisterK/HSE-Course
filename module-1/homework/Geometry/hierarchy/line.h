#pragma once
#include "point.h"

struct Line{
    double A;
    double B;
    double C;


    Line() = default;
    Line(Point A_, Point B_);

    bool operator ==(const Line& rhs) const;
    bool operator !=(const Line& rhs) const;

    double distToPoint(const Point point) const;
};