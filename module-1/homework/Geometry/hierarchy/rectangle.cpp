#include "rectangle.h"
#include "extra.h"

Rectangle::Rectangle(Point top_, Point bottom_, double ratio_):A(top_),C(bottom_),ratio(ratio_){
    double diagonal = extra::distance(A,C);
    double width = diagonal / sqrt(1 + ratio * ratio);
    double height = sqrt(diagonal * diagonal - width * width);

    Point B = A + Point(width,0);
    Point D = C - Point(width,0);
    points = {A,B,C,D};
}
std::pair<Line,Line> Rectangle::diagonals(){
    Line main = Line(A,C);
    Line secondary = Line(points[1],points[3]);
    return std::make_pair(main,secondary);
};

Point Rectangle::center(){
    return(Point((A + C) * 0.5));
}