#include "Team2.hpp"
using namespace ariel;


Team2::Team2(Character *leader) : Team(leader){} // constructor initialization list

void Team2 :: attack (Team* enemy_team) {
    // Check if the enemy is null.
    if (enemy_team == nullptr) {
        throw std::invalid_argument("Enemy team can't be null!\n");
    }
    // Check if this team trying to attack itself.
    if (this == enemy_team) {
        throw std::runtime_error("Team can't attack itself!\n");
    }
    // If this team or the enemy team is dead, throw.
    if (stillAlive() == 0 || enemy_team -> stillAlive() == 0) {
        throw std::runtime_error("This team and the enemy team must be alive!\n");
    }
    // If the current leader is dead, assign a new leader.
    if (!getLeader() -> isAlive()) {
        setLeader(closest_to_leader(this, getLeader()));
    }
    Cowboy* current_cowboy;
    Ninja* current_ninja;
    Character* victim = closest_to_leader(enemy_team, getLeader());
    // Attack enemy team.
    for (size_t i = 0; i < getWarriorsCount() && victim -> isAlive(); i++) {
        auto &temp_warrior = *getWarriors().at(i);
        if (typeid(temp_warrior) == typeid(Cowboy)) {
            current_cowboy = dynamic_cast <Cowboy*> (getWarriors().at(i));
            // Only if the cowboy is alive, shoot/reload.
            if (current_cowboy -> isAlive()) {
                // If the cowboy has bullets, shoot the victim.
                if (current_cowboy -> hasboolets()) {
                    current_cowboy -> shoot(victim);
                    // If the victim is dead, replace him.
                    if (!victim -> isAlive()) {
                        victim = closest_to_leader(enemy_team, getLeader());
                    }
                }
                // Else, reload the weapon.
                else {
                    current_cowboy -> reload();
                }
            }
        } else {
            current_ninja = dynamic_cast <Ninja*> (getWarriors().at(i));
            // Only if the ninja is alive, slash/move.
            if (current_ninja -> isAlive()) {
                // If the ninja is close, slash the victim.
                if (current_ninja -> getLocation().distance(victim -> getLocation()) <= 1) {
                    current_ninja -> slash(victim);
                    // If the victim is dead, replace him.
                    if (!victim -> isAlive()) {
                        victim = closest_to_leader(enemy_team, getLeader());
                    }
                }
                // Else, move ninja towards victim.
                else {
                    current_ninja -> move(victim);
                }
            }
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