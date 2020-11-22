#include "triangle.h"
#include "extra.h"

Triangle::Triangle(Point A_, Point B_, Point C_):Polygon({A_,B_,C_}){}


Circle Triangle::circumscribedCircle(){
    Point A = points[0];
    Point B = points[1];
    Point C = points[2];
    double D = 2 *
            (A.x * (B.y - C.y)
            + B.x * (C.y - A.y)
            + C.x * (A.y - B.y));
    double Ux = ((A.x * A.x + A.y * A.y) * (B.y -C.y) +
            (B.x * B.x + B.y * B.y) * (C.y - A.y) +
            (C.x * C.x + C.y * C.y) * (A.y - B.y)) / D;
    double Uy = ((A.x * A.x + A.y * A.y) * (C.x - B.x) +
                 (B.x * B.x + B.y * B.y) * (A.x - C.x) +
                 (C.x * C.x + C.y * C.y) * (B.x - A.x)) / D;
    Point center = Point(Ux,Uy);
    double radius = extra::distance(center,A);
    return Circle(center, radius);
}
Circle Triangle::inscribedCircle(){
    Point A = points[0];
    Point B = points[1];
    Point C = points[2];

    double side_a = extra::distance(B,C);
    double side_b = extra::distance(A,C);
    double side_c = extra::distance(A,B);

    double x_coordinate = (A.x * side_a + B.x * side_b + C.x * side_c)/
            (side_a + side_b + side_c);
    double y_coordinate = (A.y * side_a + B.y * side_b + C.y * side_c)/
                          (side_a + side_b + side_c);
    Point center = {x_coordinate, y_coordinate};
    Line one_of_the_sides = Line(A,B);
    double radius = one_of_the_sides.distToPoint(center);
    return Circle(center, radius);

}