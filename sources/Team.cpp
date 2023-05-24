#include "Team.hpp"
#include <climits>
namespace ariel{

Team::Team(Character *leader) : _leader(leader){
    this->warriors.clear(); //clear the vectors at first step
    this->warriors.push_back(leader);
    if (this->_leader->IsInTeamAlready())
    {
        throw std::runtime_error("This leader is already in another team");
    }
    this->_leader->setInTeam(true);
}

Team::~Team (){
    for(size_t i = 0; i < warriors.size(); i++){
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

void Team :: attack (Team* other) {
    // Check if the enemy is null.
    if (other == nullptr) {
        throw std::invalid_argument("Other team can't be null");
    }
    // Check if this team trying to attack itself.
    if (this == other) {
        throw std::runtime_error("Team can't attack herself");
    }
    if (stillAlive() == 0 || other -> stillAlive() == 0) {
        throw std::runtime_error("This team and the other team needs to be alive");
    }
    if (_leader -> isAlive() == false) {
        _leader = closest_to_leader(this, _leader);
    }
    Cowboy* current_cowboy;
    Ninja* current_ninja;
    Character* victim = closest_to_leader(other, _leader);
    for (size_t i = 0; i < warriors.size() && victim -> isAlive(); i++) {
        auto &temp_warrior = *warriors.at(i);
        if (typeid(temp_warrior) == typeid(Cowboy)) {
            current_cowboy = dynamic_cast <Cowboy*> (warriors.at(i));
            if (current_cowboy -> isAlive()) {
                if (current_cowboy -> hasboolets()) {
                    current_cowboy -> shoot(victim);
                    if (victim -> isAlive() == false) { // If victim dead, replace
                        victim = closest_to_leader(other, _leader);
                    }
                }
                else {
                    current_cowboy -> reload();
                }
            }
        }
    }
    for (size_t i = 0; i < warriors.size() && victim -> isAlive(); i++) {
        auto &temp_warrior = *warriors.at(i);
        if (typeid(temp_warrior) != typeid(Cowboy)) {
            current_ninja = dynamic_cast <Ninja*> (warriors.at(i));
            if (current_ninja -> isAlive()) { // Only if the ninja is alive slash him.
                if (current_ninja -> getLocation().distance(victim -> getLocation()) <= 1) {
                    current_ninja -> slash(victim);
                    if (!victim -> isAlive()) { // If the victim is dead, replace him.
                        victim = closest_to_leader(other, _leader);
                    }
                }
                else {
                    current_ninja ->move(victim);
                }
            }
        }
    }
}

int Team::stillAlive(){
    int num_of_warriors_alive = 0;
    for(Character* warrior : warriors){
        if(warrior->isAlive() == true){
            num_of_warriors_alive++;    
        }
    }
    return num_of_warriors_alive;
}

void Team::print(){
    for (std::vector<Character*>::size_type i = warriors.size(); i > 0; --i){
        if (Cowboy *cowboy = dynamic_cast<Cowboy*>(warriors.at(i-1))){ // Check if the character is a Cowboy
            if (cowboy->isAlive() == true ){
                std::cout << cowboy->print() << std::endl; // Print the Cowboy details
            }
        }
        else if (Ninja *ninja = dynamic_cast<Ninja*>(warriors.at(i-1))){ // Check if the character is a Ninja
            if (ninja->isAlive() == true ){
                std::cout << ninja->print() << std::endl;
            }
        }
    }
}



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