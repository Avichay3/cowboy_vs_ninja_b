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

Team::~Team (){
    for(int i = 0; i < warriors.size(); i++){
        delete(warriors[i]);
    }
}

void Team::add(Character *toAdd){
    
    if (toAdd->IsInTeamAlready() == true){
        throw std::runtime_error("this fighter is in the team already");
    }
    if (this->warriors.size() >= MAX_WARRIORS){
        throw std::runtime_error("This team is full");
    }
    toAdd->setInTeam(true);
    this->warriors.push_back(toAdd);
}

void Team::attack(Team *other){return;}

int Team::stillAlive(){return 0;}

void Team::print(){return ;}

