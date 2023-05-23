#include "Team.hpp"
using namespace ariel;

Team::Team(Character *leader) : _leader(leader){
    this->warriors.clear(); //clear the vectors at first step
    this->warriors = {leader};
    if(this->_leader->IsInTeamAlready() == true){
        throw std::runtime_error ("This leader is already in another team");
    }
    this->_leader->setInTeam(true);
}

Team::~Team (){}

void Team::add(Character *toAdd){return;}

void Team::attack(Team *other){return;}

int Team::stillAlive(){return 0;}

void Team::print(){return ;}

