#include "ellipse.h"
#include "vector2d.h"


Ellipse::Ellipse(Point F1_, Point F2_, double a_) : F1(F1_), F2(F2_), a(a_ / 2.0){
    c = Point::distance(F1,F2) / 2.0;
    b = std::sqrt(a * a - c * c);
}

std::pair<Point, Point> Ellipse::focuses() const {
    return std::make_pair(F1,F2);
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
    return 4.0 * ((PI * a * b + (a - b) * (a - b))/(a + b));
}

double Ellipse::area() const{
    return PI * a * b;
}

bool Ellipse::operator==(const Shape& another) const{
    const auto* another_ellipse = dynamic_cast<const Ellipse*>(&another);
    if(!another_ellipse)
        return false;
    bool focuses = (F1 == another_ellipse->F1) && (F2 == another_ellipse->F2);
    return(focuses && (std::fabs(a-another_ellipse->a) < EPS));
}

bool Ellipse::isCongruentTo(const Shape& another) const{
    const auto* another_ellipse = dynamic_cast<const Ellipse*>(&another);
    if(!another_ellipse)
        return false;
    bool is_equal_focuses = std::fabs(Point::distance(F1,F2)-
                                             Point::distance(another_ellipse->F1,another_ellipse->F2))<1e-6;
    bool is_equal_distance = std::fabs(a - another_ellipse->a) < EPS;
    return (is_equal_distance && is_equal_focuses);
}

bool Ellipse::isSimilarTo(const Shape &another) const {
    const auto* another_ellipse = dynamic_cast<const Ellipse*>(&another);
    if(!another_ellipse)
        return false;
    double ratio = Point::distance(F1,F2) /
            Point::distance(another_ellipse->F1,another_ellipse->F2);
    if(a / another_ellipse->a != ratio)
        return false;
    return true;
}
bool Ellipse::containsPoint(Point point) const{
    return Point::distance(point, F1) + Point::distance(point, F2) <= 2.0 * a;
}
void Ellipse::rotate(Point center, double angle){
    angle = angle * PI / 180.0;
    Point offset_f1 = F1 - center;
    Point offset_f2 = F2 - center;
    F1.x = (offset_f1.x) * cos(angle)
                  - (offset_f1.y) * sin(angle) + center.x;
    F1.y = (offset_f1.x) * sin(angle)
                  + (offset_f1.y) * cos(angle) + center.y;
    F2.x = (offset_f2.x) * cos(angle)
           - (offset_f2.y) * sin(angle) + center.x;
    F2.y = (offset_f2.x) * sin(angle)
           + (offset_f2.y) * cos(angle) + center.y;
}
void Ellipse::reflex(Point center){
    F1 = (F1 - center) * -1 + center;
    F2 = (F2 - center) * -1 + center;
}

void Ellipse::reflex(Line axis){
    vector2d normal_of_a_line = vector2d::normal(axis);
    std::vector<Point> points = {F1,F2};
    for(size_t i = 0; i < 2; ++i){
        vector2d normal = normal_of_a_line;
        double distance = axis.distToPoint(points[i]);
        normal.x = (normal.x / normal.getLength()) * distance;
        normal.y = (normal.y / normal.getLength()) * distance;
        if(std::fabs(axis.distToPoint(Point(points[i].x + normal.x,
                                            points[i].y + normal.y)) - 0) >= 1e-6){
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
