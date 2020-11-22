#ifndef HIERARCHY_LINE_H
#define HIERARCHY_LINE_H
#include "point.h"

struct Line{
    double A;
    double B;
    double C;


    Line() = default;
    Line(Point A_, Point B_);
    Line(double, double, double);

    bool operator ==(const Line& rhs) const;
    bool operator !=(const Line& rhs) const;

    double distToPoint(const Point point) const;
};
#endif