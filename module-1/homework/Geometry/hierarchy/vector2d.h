#ifndef HIERARCHY_VECTOR2D_H
#define HIERARCHY_VECTOR2D_H


#include <cmath>

#include "point.h"
#include "line.h"

struct vector2d {

    vector2d();
    vector2d(double, double);
    vector2d(Point, Point);


    double operator^(const vector2d& other) const;
    double operator*(const vector2d& other) const;
    vector2d operator*(const double lambda) const;

    vector2d operator+(const vector2d& other) const;

    double getLength() const;
    static vector2d normal(Line p);

    double x;
    double y;
};


#endif