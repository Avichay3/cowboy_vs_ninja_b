#include <iostream>
#include "Point.hpp"
using namespace ariel;

Point::Point(double x, double y): _x(x), _y(y){}; // initialization list

double Point::distance(Point &other){ 
    return 1.0;
}

void Point::print(){
    std::cout <<"aaa"<<std::endl;
}


Point Point::moveTowards(Point &source, Point &destination, double distance){
    return Point(1, 1);
}