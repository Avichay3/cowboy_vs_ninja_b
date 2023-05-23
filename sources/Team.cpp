#include "Team.hpp"
#include <climits>
namespace ariel{

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
        delete(warriors.at(i));
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

void Team::attack(Team *other){
    if (other == nullptr){
        throw std::invalid_argument("Team from other side must be with at least one character");
    }
    if(this->stillAlive() == 0){
        throw std::invalid_argument("Team can't attack with zero warriors");
    }
     if (other == this){
        throw std::invalid_argument("You can't kill warriors that in the same team");
    }
    if(_leader->isAlive() == false){
        _leader = closest_to_leader(this, _leader);
    }
    if(_leader = nullptr){
        return;
    }
    Character* victim = other->closest_to_leader(this, _leader); // choose closest victim to leader of other team
    if (victim== nullptr){
        return;
    }
      for (auto warrior : warriors){
        if ((other->stillAlive() == 0) || (this->stillAlive() == 0)){
            return;
        }
        if(warrior->isAlive() == false){
            continue;
        }
        if(victim->isAlive() == false){
            victim = closest_to_leader(other, victim);
        }
        if((dynamic_cast<Cowboy *>(warrior) != nullptr) && (dynamic_cast<Cowboy *>(warrior)->hasboolets())){
            dynamic_cast<Cowboy *>(warrior)->shoot(victim); // Cowboy who has bullets shoots victim
        }
        else if (dynamic_cast<Cowboy *>(warrior) != nullptr){
            dynamic_cast<Cowboy *>(warrior)->reload(); // Cowboy without bullets reload his gun
        }
      }

      for (auto warrior : warriors){
        if ((other->stillAlive() == 0) || (this->stillAlive() == 0)){
            return;
        }
        if (warrior->isAlive() == false){
            continue;
        }
        if (victim->isAlive() == false){
            victim = closest_to_leader(other, victim);
        }
        if (dynamic_cast<Ninja *>(warrior) != nullptr && warrior->distance(victim) < 1){
            dynamic_cast<Ninja *>(warrior)->slash(victim); // Ninja around 1 meter of victim kills him
        }
        else if (dynamic_cast<Ninja *>(warrior) != nullptr){
            dynamic_cast<Ninja *>(warrior)->move(victim); // Ninja further than 1 meter from victim get closer
        }
    } 

}

int Team::stillAlive(){return 0;}

void Team::print(){return ;}



Character* Team::closest_to_leader(Team* team , Character *other){
    if (other == nullptr) {
        throw std::invalid_argument("Invalid leader pointer");
    }
    Point otherLocation = other->getLocation();
    Character *temp = nullptr;
    int maxValue = INT_MAX;
    for (Character* warrior : team->getWarriors()){
        if (warrior->getLocation().distance(otherLocation) < maxValue && warrior->isAlive()==true){
                maxValue = warrior->getLocation().distance(otherLocation);
                temp = warrior;
        }
    }
    return temp;
}






std::vector<Character* > Team::getWarriors(){
    return this->warriors;
}
}