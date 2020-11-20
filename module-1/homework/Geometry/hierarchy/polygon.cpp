#include "polygon.h"


#include <cmath>
#include <utility>

#include "vector2d.h"
#include "extra.h"

Polygon::Polygon(std::vector<Point> points_) : points(std::move(points_)){}


int Polygon::verticesCount() const{
    return points.size();
}

std::vector<Point> Polygon::getVertices() const{
    return points;
}

std::vector<double> Polygon::getSides() const{
    std::vector<int> sides;
    for(size_t i = 0; i < verticesCount(); ++i){
        vector2d side = vector2d(points[i], points[(i + 1) % verticesCount()]);
        sides.push_back(side.getLength());
    }
}

std::vector<double> Polygon::getAngles() const{
    std::vector<double> angles;
    for(size_t i = 0; i < verticesCount(); ++i){
        vector2d ab = vector2d(points[i],points[(i + 1) % verticesCount()]);
        vector2d ac = vector2d(points[i], points[(i - 1) % verticesCount()]);
        angles.push_back(extra::getAngel(ab,ac));
    }
    return angles;

}

bool Polygon::isConvex() const{
    vector2d ab(points[0],points[1]);
    vector2d bc(points[1],points[2]);

    bool sign = (ab^bc) > 0;
    for(size_t i = 1; i < verticesCount() - 2; ++i){
        vector2d first(points[i], points[i + 1]);
        vector2d second(points[i + 1], points[i + 2]);
        bool check = first.x * second.y - first.y * second.x > 0;
        if(sign != check)
            return false;
    }

    return true;
}

double Polygon::perimeter() const{
    double perimeter_ = 0;
    for(size_t i = 0; i < points.size() - 1; ++i){
        double length = extra::Distance(points[i], points[(i + 1) % verticesCount()]);
        perimeter_ += length;
    }
    return perimeter_;
}

double Polygon::area() const{
    double answer = 0;
    auto base = points[0];
    for(size_t i = 1; i < verticesCount() - 1; ++i){
        vector2d ab = vector2d(base,points[i]);
        vector2d ac = vector2d(base, points[i + 1]);
        answer += (ab ^ ac);
    }
    answer = std::abs(answer);
    return (answer / 2.0);
}

bool Polygon::operator==(const Shape& another) const{
    const auto* another_polygon = dynamic_cast<const Polygon*>(&another);
    if(!another_polygon)
        return false;
    if(verticesCount() != another_polygon->verticesCount())
        return false;
    for(size_t i = 0; i < verticesCount(); ++i){
        bool check_x = extra::isNotEqual(points[i].x, another_polygon->points[i].y);
        bool check_y = extra::isNotEqual(points[i].y, another_polygon->points[i].y);
        if(check_x || check_y)
            return false;
    }
    return true;
}
bool Polygon::isCongruentTo(const Shape& another) const{
    const auto* another_polygon = dynamic_cast<const Polygon*>(&another);
    if(!another_polygon)
        return false;
    if(verticesCount() != another_polygon->verticesCount())
        return false;
    std::vector<double> sides = getSides();
    std::sort(sides.begin(),sides.end());
    std::vector<double> angles = getAngles();
    std::sort(angles.begin(),angles.end());
    std::vector<double> another_sides = another_polygon->getSides();
    std::sort(another_sides.begin(),another_sides.end());
    std::vector<double> another_angles = another_polygon->getAngles();
    std::sort(another_angles.begin(),another_angles.end());
    for(size_t i = 0; i < verticesCount(); ++i){
        if(extra::isNotEqual(sides[i],another_sides[i]) || extra::isNotEqual(angles[i],another_angles[i]))
            return false;
    }
    return true;
}

bool Polygon::isSimilarTo(const Shape& another) const{
    const auto* another_polygon = dynamic_cast<const Polygon*>(&another);
    if(!another_polygon)
        return false;
    if(verticesCount() != another_polygon->verticesCount())
        return false;
    std::vector<double> sides = getSides();
    std::sort(sides.begin(),sides.end());
    std::vector<double> angles = getAngles();
    std::sort(angles.begin(),angles.end());
    std::vector<double> another_sides = another_polygon->getSides();
    std::sort(another_sides.begin(),another_sides.end());
    std::vector<double> another_angles = another_polygon->getAngles();
    std::sort(another_angles.begin(),another_angles.end());
    if(angles != another_angles)
        return false;
    double ratio = sides.front() / another_sides.front();
    for(size_t i = 0; i < verticesCount(); ++i){
        if(extra::isNotEqual(sides[i],another_sides[i] * ratio))
            return false;
    }
    return true;
}
bool Polygon::containsPoint(Point point) const{
    double area = Polygon::area();
    double another_area = 0;
    for(size_t i = 0; i < verticesCount(); ++i){
        vector2d ab = vector2d(point,points[i]);
        vector2d ac = vector2d(point, points[(i + 1) % verticesCount()]);
        another_area += ab^ac;
    }
    another_area /= 2.0;
    another_area = std::abs(another_area);
    return(extra::isEqual(area,another_area));
}

void Polygon::rotate(Point center, double angle){
    angle = extra::toRad(angle);
    for(size_t i = 0; i < verticesCount(); ++i){
        points[i].x = (points[i].x - center.x) * cos(angle)
                - (points[i].y - center.y) * sin(angle) + center.x;
        points[i].x = (points[i].y - center.y) * sin(angle)
                - (points[i].x - center.x) * cos(angle) + center.y;
    }
}
void Polygon::reflex(Point center){
    for(size_t i = 0; i < verticesCount(); ++i){
        points[i].x = 2.0 * center.x - points[i].x;
        points[i].y = 2.0 * center.y - points[i].y;
    }
}
void Polygon::reflex(Line axis){
    vector2d normal_of_a_line = vector2d::normal(axis);
    for(size_t i = 0; i < verticesCount(); ++i){
        vector2d normal = normal_of_a_line;
        double distance = axis.distToPoint(points[i]);
        normal.x = (normal.x / normal.getLength()) * distance;
        normal.y = (normal.y / normal.getLength()) * distance;
        if(extra::isNotEqual(axis.distToPoint(Point(points[i].x + normal.x, points[i].y + normal.y)),0)){
            normal = normal * -1.0;
        }
        points[i].x += 2 * normal.x;
        points[i].y += 2 * normal.y;
    }
}

void scale(Point center, double coefficient){

}