#include "polygon.h"
#include "vector2d.h"

Polygon::Polygon(std::vector<Point> points_) : points(std::move(points_)){}


size_t Polygon::verticesCount() const{
    return points.size();
}

std::vector<Point> Polygon::getVertices() const{
    return points;
}

std::vector<double> Polygon::getSides() const{
    std::vector<double> sides;
    for(size_t i = 0; i < verticesCount(); ++i){
        double side = Point::distance(points[i], points[(i + 1) % verticesCount()]);
        sides.push_back(side);
    }
    return sides;
}

std::vector<double> Polygon::getAngles() const{
    std::vector<double> angles;
    for(size_t i = 0; i < verticesCount(); ++i){
        vector2d ab = vector2d(points[i],points[(i + 1) % verticesCount()]);
        vector2d ac = vector2d(points[i], points[(i - 1) % verticesCount()]);
        angles.push_back(vector2d::getAngle(ab,ac));
    }
    return angles;

}

bool Polygon::isConvex() const{
    vector2d ab(points[1],points[2]);
    vector2d bc(points[1],points[0]);

    bool sign = (ab^bc) > 0;
    for(size_t i = 0; i < verticesCount(); ++i){
        vector2d first(points[i], points[(i + 1) % verticesCount()]);
        vector2d second(points[i], points[(i - 1) % verticesCount()]);
        bool check = (first ^ second) > 0;
        if(sign != check)
            return false;
    }

    return true;
}

double Polygon::perimeter() const{
    double perimeter_ = 0;
    for(size_t i = 0; i < points.size(); ++i){
        double length = Point::distance(points[i], points[(i + 1) % verticesCount()]);
        perimeter_ += length;
    }
    return perimeter_;
}

double Polygon::area() const{
    double answer = 0;
    for(size_t i = 0; i < verticesCount(); ++i){
        answer += points[i].x * points[(i + 1) % verticesCount()].y -
                points[i].y * points[(i + 1) % verticesCount()].x;
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
        if(!another_polygon->containsPoint(points[i]))
            return false;
    }
    for(size_t i = 0; i < verticesCount(); ++i) {
        if(!containsPoint(another_polygon->points[i]))
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
        if(std::fabs(sides[i] - another_sides[i]) >= EPS ||
                            std::fabs(angles[i] - another_angles[i]) >= EPS)
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
        if(std::fabs(sides[i] - another_sides[i] * ratio) >= EPS)
            return false;
    }
    return true;
}
bool Polygon::containsPoint(Point point) const{
    double angles = 0;
    for(size_t i = 0; i < verticesCount(); ++i){
        Point A = points[i];
        Point B = points[(i + 1) % verticesCount()];
        if(std::fabs(Point::distance(A,B) - Point::distance(A,point)
                                          - Point::distance(B,point)) < EPS)
            return true;
        vector2d point_to_A = vector2d(point,A);
        vector2d point_to_B = vector2d(point,B);
        angles += vector2d::getAngle(point_to_A,point_to_B);
    }
    angles = std::abs(angles);
    return (std::fabs(angles - 2 * PI) < EPS);
}

void Polygon::rotate(Point center, double angle){
    angle = angle * PI / 180.0;
    for(size_t i = 0; i < verticesCount(); ++i){
        Point offset = points[i] - center;
        points[i].x = (offset.x) * cos(angle) - (offset.y) * sin(angle) + center.x;
        points[i].y = (offset.x) * sin(angle) + (offset.y) * cos(angle) + center.y;
    }
}
void Polygon::reflex(Point center){
    for(size_t i = 0; i < verticesCount(); ++i){
        points[i] = (points[i] - center) * -1 + center;
    }
}
void Polygon::reflex(Line axis){
    vector2d normal_of_a_line = vector2d::normal(axis);
    for(size_t i = 0; i < verticesCount(); ++i){
        vector2d normal = normal_of_a_line;
        double distance = axis.distToPoint(points[i]);
        double length = normal.getLength();
        normal.x = (normal.x / length) * distance;
        normal.y = (normal.y / length) * distance;
        if(axis.distToPoint(Point(points[i].x + normal.x,
                                            points[i].y + normal.y)) >= EPS){
            normal = normal * -1.0;
        }
        points[i].x += 2 * normal.x;
        points[i].y += 2 * normal.y;
    }
}

void Polygon::scale(Point center, double coefficient){
    for(size_t i = 0; i < verticesCount(); ++i){
        points[i].x = (points[i].x - center.x) * coefficient + center.x;
        points[i].y = (points[i].y - center.y) * coefficient + center.y;
    }
}