#pragma once

#include "shape.h"

class Polygon : public Shape{
public:

    Polygon() = default;

    Polygon(std::vector<Point> points_);

    int verticesCount() const;
    std::vector<Point> getVertices() const;
    std::vector<double> getSides() const;
    std::vector<double> getAngles() const;
    bool isConvex() const;


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
protected:
    std::vector<Point> points;
};

