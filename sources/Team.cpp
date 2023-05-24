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

void Team::attack(Team *enemies){
    if (enemies == nullptr){
        throw std::invalid_argument("enemies must be with at least one character");
    }
    if (this->stillAlive() == 0 || enemies->stillAlive() == 0){
        throw std::runtime_error("Team can't attack with no warriors");
    }
    if (enemies == this){
        throw std::invalid_argument("There is no internal kills");
    }
    if ((_leader->isAlive() == false)){
        _leader->setInTeam(false);
        this->setLeader(closest_to_leader(this, _leader));
    }
    if ((enemies->getLeader()->isAlive() == false)){
        enemies->getLeader()->setInTeam(false);
        enemies->setLeader(closest_to_leader(enemies, enemies->getLeader()));
    }
    if ((enemies->getLeader() == nullptr) || (this->getLeader() == nullptr)){
        return;
    }
    Character *victim = closest_to_leader(enemies, this->_leader);
    if (victim == nullptr){
        return;
    }
    for (auto warrior : warriors){
        if ((enemies->stillAlive() == 0) || (this->stillAlive() == 0)){
            return;
        }
        if ((warrior->isAlive() == false)){
            continue;
        }
        if((victim->isAlive() == false)){
            victim = closest_to_leader(enemies, victim);
        }
        if ((dynamic_cast<Cowboy *>(warrior) != nullptr) && (dynamic_cast<Cowboy *>(warrior)->hasboolets())){
            dynamic_cast<Cowboy *>(warrior)->shoot(victim);
        }
        else if (dynamic_cast<Cowboy *>(warrior) != nullptr){
            dynamic_cast<Cowboy *>(warrior)->reload();
        }
    }
    for (auto warrior : warriors){
        if ((enemies->stillAlive() == 0) || (this->stillAlive() == 0)){
            return;
        }
        if((warrior->isAlive() == false)){
            continue;
        }
        if ((victim->isAlive() == false)){
            victim = closest_to_leader(enemies, victim);
        }
        if (dynamic_cast<Ninja *>(warrior) != nullptr && warrior->distance(victim) < 1){
            dynamic_cast<Ninja *>(warrior)->slash(victim);
        }
        else if (dynamic_cast<Ninja *>(warrior) != nullptr){
            dynamic_cast<Ninja *>(warrior)->move(victim);
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