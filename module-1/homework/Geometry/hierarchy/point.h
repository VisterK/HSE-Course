#ifndef HIERARCHY_POINT_H
#define HIERARCHY_POINT_H


struct Point{

    Point() = default;
    Point(double, double);

    bool operator==(const Point& rhs) const;
    bool operator!=(const Point& rhs) const;
    Point operator+(const Point& rhs) const;
    Point operator-(const Point& rhs) const;
    Point operator*(const double lambda) const;

    double x, y;
};
#endif