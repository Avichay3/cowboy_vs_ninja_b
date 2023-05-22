#include "Ninja.hpp"
using namespace ariel;

Ninja::Ninja(std::string name, Point location, int hit_points, int speed) : 
Character(name,location,hit_points),_speed(speed){} //constructor


Ninja::Ninja(std::string name, Point location) : Character(name, location){}

void Ninja::move(Character *other){
    return;
}

void Ninja::slash(Character *other){
    return;
}

std::string Ninja::print() {
    return "  ";
}



