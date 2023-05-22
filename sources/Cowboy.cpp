#include "Cowboy.hpp"
using namespace ariel;

Cowboy::Cowboy(std::string name, Point location) : Character(name, location, 110){}; //initialization list

void Cowboy::shoot(Character *other){
    return;
}

bool Cowboy::hasBullets() const {
    return false;
}

void Cowboy::reload(){
    return;
}

std::string Cowboy::print(){
    return "";
}