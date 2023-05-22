#include "Team.hpp"
using namespace ariel;

Team::Team(Character *leader) : _leader(leader){}

Team::~Team (){}

void Team::add(Character *toAdd){return;}

void Team::attack(Team *other){return;}

int Team::stillAlive(){return 0;}

std::string Team::print(){return " ";}

