#include "Character.hpp"
#include "Cowboy.hpp"
using namespace ariel;

Cowboy::Cowboy(std::string name, Point location) : Character(name, location, 110), _num_of_bullets{} //initialization list

void Cowboy::shoot(Character* other){
    if ((this->isAlive() == false) || (other->isAlive() == false)){
        throw ("Cowboy can't attack when he or his enemy is dead");
    }
    if (this == other){
        throw ("Cowboy can't attack himself");
    }
    if (this->hasBullets()){
        other->hit(10);
        this->_num_of_bullets = _num_of_bullets - 1;
    }
}

bool Cowboy::hasBullets() const {
    return this->_num_of_bullets > 0;
}


int Cowboy::getBullets() const{
    return this->_num_of_bullets;
}

void Cowboy::reload(){
     if ((this->isAlive() == false)){
        throw ("Dead cowboy can't reload");
    }
    this->_num_of_bullets = 6;
}

std::string Cowboy::print(){
    std::string print = "";
    print = print + "(" + this->getName() + ")";
    if (this->isAlive() == true){
        print += " hit_points: " + std::to_string(this->get_hit_points());
    }
    print += " The location: (" + std::to_string(this->getLocation().getX()) + std::to_string(this->getLocation().getY())+ ")";
    return print;
}