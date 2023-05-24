#include "Team2.hpp"
using namespace ariel;


Team2::Team2(Character *leader) : Team(leader){} // constructor initialization list

void Team2::attack(Team* other) {
    if (!other || other == this) {
        throw std::invalid_argument("Invalid target team");
    }

    if (this->stillAlive() == 0 || other->stillAlive() == 0) {
        throw std::invalid_argument("Both teams must have warriors");
    }

    if (!this->getLeader()->isAlive()) {
        this->setLeader(closest_to_leader(this, this->getLeader()));
    }

    if (!other->getLeader()->isAlive()) {
        other->setLeader(closest_to_leader(other, other->getLeader()));
    }

    Character* victim = closest_to_leader(other, this->getLeader());
    if (!victim) {
        return;
    }
    for (auto warrior : this->getWarriors()) {
        if (!other->stillAlive() || !this->stillAlive()) {
            return;
        }
        if (warrior->isAlive() == false) {
            continue;
        }
        if (victim->isAlive() == false) {
            victim = closest_to_leader(other, victim);
        }

        Cowboy* cowboy = dynamic_cast<Cowboy*>(warrior);
        Ninja* ninja = dynamic_cast<Ninja*>(warrior);

        if (cowboy && cowboy->getBullets() > 0) {
            cowboy->shoot(victim);
        } else if (cowboy) {
            cowboy->reload();
        } else if (ninja && warrior->distance(victim) <= 1) {
            ninja->slash(victim);
        } else if (ninja) {
            ninja->move(victim);
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