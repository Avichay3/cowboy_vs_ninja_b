#include "SmartTeam.hpp"
#include <limits>
using namespace ariel;
/**

Constructor for the SmartTeam class.
Creates a new team with the given character as the leader and uses Team constructor as it's the base class.
@param character A pointer to the character to be set as the leader of the team.
@throws runtime_error if the leader character is already in another team.
*/
SmartTeam::SmartTeam(Character *leader) : Team(leader)
{
}
/**
 * Performs an attack on an enemy team.
 *
 * Throws an exception if:
 * - The enemy team is null.
 * - The current team has no warriors.
 * - The enemy team has no warriors.
 * - The enemy team is the same as the current team.
 *
 * @param enemies A pointer to the enemy team to be attacked.
 * @throws std::invalid_argument if enemies is null or has no characters, std::runtime_error if the current team has no warriors,
 *         std::invalid_argument if the enemy team is the same as the current team.
 */
void SmartTeam::attack(Team *enemies){
    if (enemies == nullptr){
        throw std::invalid_argument("enemies must be with at least one character");
    }

    if (this->stillAlive() == 0){
        throw std::invalid_argument("Team can't attack with no warriors");
    }

    if (enemies->stillAlive() == 0){
        throw std::runtime_error("Can't attack team with no warriors");
    }

    if (enemies == this){
        throw std::invalid_argument("There is no internal kills");
    }

    // Check if leader is alive
    if ((this->getLeader()->isAlive()) == false){
        this->getLeader()->setInTeam(false);
        this->setLeader(closest_to_leader(this, this->getLeader()));
    }
    // Find closest living enemy to leader
    if (!(enemies->getLeader()->isAlive()))
    {
        enemies->getLeader()->setInTeam(false);
        enemies->setLeader(closest_to_leader(enemies, enemies->getLeader()));
    }
    if ((enemies->getLeader() == nullptr) || (this->getLeader() == nullptr))
    {
        return;
    }
    // the closer enemy to this team
    Character* closest_enemy = findClosestCharacters(this, enemies)[1];
    if (!closest_enemy){
        return;
    }
    // Attack victim with all living members
    for (auto warrior : this->getWarriors())
    {
        if ((enemies->stillAlive() == 0) || (this->stillAlive() == 0)){
            return;
        }

        if (!(warrior->isAlive())){
            continue;
        }

        if (!(closest_enemy->isAlive())){
            closest_enemy = findClosestCharacters(this, enemies)[1];
        }

        if (dynamic_cast<Cowboy *>(warrior) != nullptr && dynamic_cast<Cowboy *>(warrior)->getBullets() > 0){
            // Cowboy with bullets shoots closest enemy
            dynamic_cast<Cowboy *>(warrior)->shoot(closest_enemy);
        }

        else if (dynamic_cast<Cowboy *>(warrior) != nullptr){
            // Cowboy without bullets loads gun
            dynamic_cast<Cowboy *>(warrior)->reload();
        }

        else if (dynamic_cast<Ninja *>(warrior) != nullptr && warrior->distance(closest_enemy) <= 1){
            // Ninja within 1 meter of closest enemy kills closest enemy
            dynamic_cast<Ninja *>(warrior)->slash(closest_enemy);
        }
        else if (dynamic_cast<Ninja *>(warrior) != nullptr){
            // Ninja further than 1 meter from closest enemy moves closer
            dynamic_cast<Ninja *>(warrior)->move(closest_enemy);
        }
    }
}
/**
 * Finds the closest characters between the attacker team and the enemy team.
 *
 * @param attackerTeam A pointer to the attacker team.
 * @param enemyTeam A pointer to the enemy team.
 * @return A vector of pointers to the closest characters, with size 2.
 */
std::vector<Character*> SmartTeam::findClosestCharacters(Team* attackerTeam, Team* enemyTeam) {
std::vector<Character*> closest_characters{2};

    double minDistance = std::numeric_limits<double>::max();


    for (auto attacker : attackerTeam->getWarriors()) {
        for (auto enemy : enemyTeam->getWarriors()) {
            double dist = attacker->distance(enemy);
            if (dist < minDistance && attacker->isAlive() && enemy->isAlive()) {
                minDistance = dist;
                closest_characters.at(0) = attacker;
                closest_characters.at(1) = enemy;
            }
        }
    }
    return closest_characters;
}