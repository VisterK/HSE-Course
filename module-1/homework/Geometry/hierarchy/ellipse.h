#pragma once

#include "shape.h"

class Ellipse : public Shape{
public:

    Ellipse(Point, Point, double);

    std::pair<Point, Point> focuses() const;
    std::pair<Line, Line> directrices();
    double eccentricity();
    Point center();

    double perimeter() const override;
    double area() const override;

    bool operator==(const Shape& another) const override;
    bool isCongruentTo(const Shape& another) const override;
    bool isSimilarTo(const Shape& another) const override;
    bool containsPoint(Point point) const override;

    void rotate(Point center, double angle) override;
    void reflex(Point center) override;
    void reflex(Line axis) override;
    void scale(Point center, double coefficient) override;
private:
    Point F1;
    Point F2;

    double a;
    double b;
    double c;
};