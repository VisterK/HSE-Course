#pragma once


struct Line;

struct Point{

    Point() = default;
    Point(double, double);

    bool operator==(const Point& rhs) const;
    bool operator!=(const Point& rhs) const;

    double x, y;
};