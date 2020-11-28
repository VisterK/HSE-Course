#include "rectangle.h"

Rectangle::Rectangle(Point top_, Point bottom_, double ratio_):A(top_),C(bottom_),ratio(ratio_){
    double min_x = std::min(A.x, C.x);
    double max_x = std::max(A.x, C.x);
    double min_y = std::min(A.y, C.y);
    double max_y = std::max(A.y, C.y);
    points = {Point(max_x,min_y),Point(max_x,max_y),Point(min_x,max_y),Point(min_x,min_y)};
}
std::pair<Line,Line> Rectangle::diagonals(){
    Line main = Line(A,C);
    Line secondary = Line(points[1],points[3]);
    return std::make_pair(main,secondary);
};

Point Rectangle::center(){
    return(Point((A + C) * 0.5));
}