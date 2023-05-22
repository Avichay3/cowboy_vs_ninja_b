#include <iostream>
#include "Point.hpp"
#include <math.h>
using namespace ariel;

Point::Point(double x, double y): _x(x), _y(y){}; // constructor initialization list

double Point::distance(const Point &other) const { 
    double dist = sqrt(pow(this->_x - other.getX(), 2) + pow((this->_y - other.getY()),2));
    return dist;
}

void Point::print(){
    std::cout<<"(" <<this->_x <<"," <<this->_y <<")" <<std::endl;
}

/*this next function gets an source point and destination and also distance.
The function return the closest point to the destination point that found 
at most at the given distance from the point of the origin*/
Point Point::moveTowards(Point &source, Point &destination, double distance){
    if(distance < 0)
        throw ("distance cannot be smaller than 0");
    double distance2 = source.distance(destination); // distance between source to destination
    if(distance2 <= distance)
        return destination;
    Point to_return ((source.getX() + (distance * (destination.getX() - source.getX()) / distance2)), (source.getY() + (distance * (destination.getY()-source.getY()) / distance2)));    
    return to_return;
}

double Point::getX() const{
    return this->_x;
}

double Point::getY() const{
    return this->_y;
}