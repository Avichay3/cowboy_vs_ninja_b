#include "Character.hpp"
using namespace ariel;


Character::Character(std::string name, Point &location, int hit_points) : 
_name(name), _location(location), _hit_points(hit_points) {} //first constructor with initialization list


Character::Character(std::string name, Point &location): _name(name), _location(location){}

bool Character::isAlive() const{
	return this->_hit_points > 0;
}

double Character::distance(Character *other){
    Point p1 = this->getLocation();
    Point p2 = other->getLocation();
    return p1.distance(p2);
}

bool Character::IsInTeamAlready() {
    return this->_is_in_team_already;
}


void Character::hit(int hit_points){
    if(hit_points < 0){
        throw ("hit points cannot be a negative number");
    }
    this->_hit_points = this->_hit_points - hit_points;
}

std::string Character::getName() const{
	return _name;
}

Point Character::getLocation() const{
    return this->_location;
}

std::string Character::print(){
    return " " ;
}

int Character::get_hit_points() const{
    return this->_hit_points;
}

void Character::setInTeam(bool b){
    this->_is_in_team_already = b;
}