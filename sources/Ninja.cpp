#include "Ninja.hpp"
#include <string.h>
using namespace ariel;

Ninja::Ninja(std::string name, Point location, int hit_points, int speed) : 
Character(name,location,hit_points),_speed(speed){} //constructor


Ninja::Ninja(std::string name, Point location) : Character(name, location){}

void Ninja::move(Character *other){
    this->_location = Point::moveTowards(this->getLocation(),other->getLocation(),this->_speed);
}

void Ninja::slash(Character *other) {
    if((this->isAlive() == false) || (other->isAlive() == false)){
        throw std::runtime_error("The Ninja can't attack when he or his enemy dead");
    }
    if(this == other){
        throw std::runtime_error("The Ninja can't slash himself");
    }
    if((this->distance(other) < 1)){
        other->hit(40);
    }
}

std::string Ninja::print() {
    std::string print = "";
    print = print + "Ninja (" + this->getName() + ")";
    if(this->isAlive() == true){
        print += " hit_points: " + std::to_string(this->get_hit_points());
    }
    print += " The location: (" + std::to_string(this->getLocation().getX()) + ", " + std::to_string(this->getLocation().getY()) + ")";
    return print;
}

int Ninja :: getSpeed ()const { 
    return _speed; 
}



