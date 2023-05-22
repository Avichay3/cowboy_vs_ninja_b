#include "Character.hpp"
using namespace ariel;


Character::Character(std::string name, Point &location, int hit_points) : 
_name(name), _location(location), _hit_points(hit_points) {} //first constructor with initialization list


Character::Character(std::string name, Point &location): _name(name), _location(location){}

bool Character::isAlive() {
	return false;
}

double ariel::Character::distance(Point *other){
    return (double)1;
}


void Character::hit(int){
    std::cout<<"hit"<<std::endl;
}

std::string Character::getName() const{
	return _name;
}

Point Character::getLocation() {
    return Point(1.0,2.0);
}

std::string Character::print(){
    return "";
}