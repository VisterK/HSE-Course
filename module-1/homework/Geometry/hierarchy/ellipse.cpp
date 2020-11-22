#include "ellipse.h"
#include "extra.h"

#include <cmath>

Ellipse::Ellipse(Point F1_, Point F2_, double a_) : F1(F1_), F2(F2_), a(a_ / 2.0){
    c = extra::distance(F1,F2) / 2.0;
    b = std::sqrt(a * a - c * c);
}

std::pair<Point, Point> Ellipse::focuses() const {
    return {F1, F2};
}

std::pair<Line, Line> Ellipse::directrices(){
    Line first(0,1,a/eccentricity());
    Line second(0,1, -a/eccentricity());
    return std::make_pair(first,second);
}

double Ellipse::eccentricity(){
    return c / a;
}

Point Ellipse::center(){
    return Point((F1.x + F2.x) / 2.0, (F1.y + F2.y) / 2.0);
}

double Ellipse::perimeter() const{
    double L =  4.0 * ((extra::PI * a * b + (a - b) * (a - b))/(a + b));
    return L;
}

double Ellipse::area() const{
    return extra::PI * a * b;
}

bool Ellipse::operator==(const Shape& another) const{
    const auto* another_ellipse = dynamic_cast<const Ellipse*>(&another);
    if(!another_ellipse)
        return false;
    bool focuses = extra::isEqual(F1, another_ellipse->F1) && extra::isEqual(F2, another_ellipse->F2);
    return(focuses && extra::isEqual(a,another_ellipse->a));
}

bool Ellipse::isCongruentTo(const Shape& another) const{
    const auto* another_ellipse = dynamic_cast<const Ellipse*>(&another);
    if(!another_ellipse)
        return false;
    bool is_equal_focuses = extra::isEqual(extra::distance(F1,F2),
                                             extra::distance(another_ellipse->F1,another_ellipse->F2));
    bool is_equal_distance = extra::isEqual(a,another_ellipse->a);
    return (is_equal_distance && is_equal_focuses);
}

bool Ellipse::isSimilarTo(const Shape &another) const {
    const auto* another_ellipse = dynamic_cast<const Ellipse*>(&another);
    if(!another_ellipse)
        return false;
    double ratio = extra::distance(F1,F2) /
            extra::distance(another_ellipse->F1,another_ellipse->F2);
    if(a / another_ellipse->a != ratio)
        return false;
    return true;
}
bool Ellipse::containsPoint(Point point) const{
    return extra::distance(point, F1) + extra::distance(point, F2) <= 2.0 * a;
}
void Ellipse::rotate(Point center, double angle){
    angle = extra::toRad(angle);
    F1.x = (F1.x - center.x) * cos(angle)
                  - (F1.y - center.y) * sin(angle) + center.x;
    F1.y = (F1.y - center.y) * sin(angle)
                  - (F1.x - center.x) * cos(angle) + center.y;
    F2.x = (F2.x - center.x) * cos(angle)
           - (F2.y - center.y) * sin(angle) + center.x;
    F2.y = (F2.y - center.y) * sin(angle)
           - (F2.x - center.x) * cos(angle) + center.y;
}
void Ellipse::reflex(Point center){
    F1.x = 2.0 * center.x - F1.x;
    F1.y = 2.0 * center.y - F1.y;

    F2.x = 2.0 * center.x - F2.x;
    F2.y = 2.0 * center.y - F2.y;
}

void Ellipse::reflex(Line axis){
    vector2d normal_of_a_line = vector2d::normal(axis);
    std::vector<Point> points = {F1,F2};
    for(size_t i = 0; i < 2; ++i){
        vector2d normal = normal_of_a_line;
        double distance = axis.distToPoint(points[i]);
        normal.x = (normal.x / normal.getLength()) * distance;
        normal.y = (normal.y / normal.getLength()) * distance;
        if(extra::isNotEqual(axis.distToPoint(Point(points[i].x + normal.x,
                                                    points[i].y + normal.y)),0)){
            normal = normal * -1.0;
        }
        points[i].x += 2 * normal.x;
        points[i].y += 2 * normal.y;
    }
    F1 = points[0];
    F2 = points[1];
}

void Ellipse::scale(Point center, double coefficient){
    std::vector<Point> points = {F1,F2};
    for(size_t i = 0; i < 2; ++i){
        points[i].x = (points[i].x - center.x) * coefficient + center.x;
        points[i].y = (points[i].y - center.y) * coefficient + center.y;
    }
    F1 = points[0];
    F2 = points[1];
    a *= coefficient;
}
