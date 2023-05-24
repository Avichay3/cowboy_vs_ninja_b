#include "Team2.hpp"
using namespace ariel;


Team2::Team2(Character *leader) : Team(leader){} // constructor initialization list

void Team2::attack(Team *other){
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
    if(_leader == nullptr){
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




int Team2::stillAlive(){
    int num_of_warriors_alive = 0;
    for(Character* warrior : warriors){
        if(warrior->isAlive() == true){
            num_of_warriors_alive++;    
        }
    }
    return num_of_warriors_alive;
}


void Team2::print(){
    for (size_t i = 0; i < stillAlive(); i++) {
        std::cout << getWarriors().at(i) -> print() << std::endl;
    }
}