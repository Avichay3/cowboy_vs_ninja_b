#include "SmartTeam.hpp"
#include <limits>
using namespace std;
using namespace ariel;

/**
 * Attacks enemy_team with a smart strategy.
 */
void SmartTeam :: attack (Team* enemy_team) {
    // Check if the enemy is null.
    if (enemy_team == nullptr) {
        throw invalid_argument("Enemy team can't be null!\n");
    }
    // Check if this team trying to attack itself.
    if (this == enemy_team) {
        throw runtime_error("Team can't attack itself!\n");
    }
    // If this team or the enemy team is dead, throw.
    if (stillAlive() == 0 || enemy_team->stillAlive() == 0) {
        throw runtime_error("This team and the enemy team must be alive!\n");
    }
    // If the current leader is dead, assign a new leader.
    if (!getLeader()->isAlive()) {
        setLeader(closest_to_leader(this, getLeader()));
    }
    Cowboy* current_cowboy = nullptr;
    Ninja* current_ninja = nullptr;
    Character* victim = nullptr;
    // Iterate first over the ninjas since they have distance limit.
    for (size_t i = 0; i < getWarriorsCount(); i++) {
        auto &temp_warrior = *getWarriors().at(i);
        if (typeid(temp_warrior) != typeid(Cowboy)) {
            current_ninja = dynamic_cast <Ninja*> (getWarriors().at(i));
            // Only if the ninja is alive, pick a target for him.
            if (current_ninja -> isAlive()) {
                // Choose a victim for the ninja.
                victim = locate_ninja_target(current_ninja, enemy_team);
                // If the enemy team is dead, break.
                if (victim == nullptr) { break; }
                // If the ninja is close, slash the victim.
                if (current_ninja -> distance(victim) <= 1) {
                    current_ninja -> slash(victim);
                }
                // Else, move ninja towards victim.
                else {
                    current_ninja -> move(victim);
                }
            }
        }
    }
    // Iterate now over the cowboys.
    for (size_t i = 0; i < getWarriorsCount(); i++) {
        auto &temp_warrior = *getWarriors().at(i);
        if (typeid(temp_warrior) == typeid(Cowboy)) {
            current_cowboy = dynamic_cast <Cowboy*> (getWarriors().at(i));
            // Only if the cowboy is alive, pick a target for him.
            if (current_cowboy -> isAlive()) {
                // If the cowboy has bullets.
                if (current_cowboy -> hasboolets()) {
                    // Choose a victim for the cowboy.
                    victim = Locate_cowboy_target(enemy_team);
                    // If the enemy team is dead, break.
                    if (victim == nullptr) { 
                        break; 
                    }
                    // Shoot the victim.
                    current_cowboy -> shoot(victim);
                }
                // Else, reload the weapon.
                else {
                    current_cowboy -> reload();
                }
            }
        }
    }
}

/**
 * For a ninja, we would try to look for a victim with low hp which we can hit right away (meaning without moving),
 * or if we can't right away, we will prefer in one move and than slash (distance <= "speed").
 * Otherwise, the victim is far so we will want him to be close as possible (reduce move() calls).
 * We define "low hp" as the lowest hp closest to 40. We want to leave those with the real lowest hp to the cowboys.
 * @param ninja - The current ninja attacker.
 * @param enemy_team - The team we will choose a victim from.
 * @return - A pointer to a valid victim or nullptr if all members are dead.
 */
Character* SmartTeam :: locate_ninja_target (Ninja* ninja, Team* enemy_team) {
    // Alive victim which is 1 meter away at most and has low hp.
    Character* victim_a = nullptr;
    // Alive victim which is at 1 < distance <= "speed" away and has low hp.
    Character* victim_b = nullptr;
    // Alive victim which is more than "speed" distance away but closer and has low hp.
    Character* victim_c = nullptr;
    // Save the minimum distance for c type victims.
    double min_distance_c = numeric_limits <double> :: max();
    // Save the low hp for each type of victim.
    double low_hp_a = numeric_limits <double> :: max();
    double low_hp_b = numeric_limits <double> :: max();
    double low_hp_c = numeric_limits <double> :: max();
    // Current distance for a warrior in team.
    double dist = 0;
    // Current hp for a warrior in team.
    double hp = 0;
    // Iterate over the enemy team and pick a victim.
    for (size_t i = 0; i < enemy_team -> getWarriorsCount(); i++) {
        // Only if this enemy is alive, check him.
        if (enemy_team -> getWarriors().at(i) -> isAlive()) {
            // Compute distance and hp.
            dist = ninja -> distance(enemy_team -> getWarriors().at(i));
            hp = enemy_team -> getWarriors().at(i)->get_hit_points();
            // Type A victim.
            if (dist <= 1) {
                // Update type A victim and low hp if necessary.
                if ((low_hp_a > NINJA_DAMAGE && hp < low_hp_a) ||
                    (low_hp_a <= NINJA_DAMAGE && hp <= NINJA_DAMAGE && hp > low_hp_a)) {
                    low_hp_a = hp;
                    victim_a = enemy_team -> getWarriors().at(i);
                }
            }
            // Type B victim.
            else if (dist <= ninja -> getSpeed()) {
                // Update type B victim and low hp if necessary.
                if ((low_hp_b > NINJA_DAMAGE && hp < low_hp_b) ||
                    (low_hp_b <= NINJA_DAMAGE && hp <= NINJA_DAMAGE && hp > low_hp_b)) {
                    low_hp_b = hp;
                    victim_b = enemy_team -> getWarriors().at(i);
                }
            }
            // Type C victim.
            else {
                // Update type C victim and min distance if necessary.
                if (dist < min_distance_c) {
                    min_distance_c = dist;
                    victim_c = enemy_team -> getWarriors().at(i);
                }
                // If we found a victim within the same distance with low hp.
                else if ((dist == min_distance_c) && ((low_hp_c > NINJA_DAMAGE && hp < low_hp_c) ||
                         (low_hp_c <= NINJA_DAMAGE && hp <= NINJA_DAMAGE && hp > low_hp_b))) {
                    low_hp_c = hp;
                    victim_c = enemy_team -> getWarriors().at(i);
                }
            }
        }
    }
    // We would prefer to return A/B/C victim in that order based on their existence.
    if (victim_a != nullptr) { return victim_a; }
    if (victim_b != nullptr) { return victim_b; }
    if (victim_c != nullptr) { return victim_c; }
    // Team is dead. Return nullptr.
    return nullptr;
}

/**
 * Chooses a victim for a cowboy. The victim will be alive and with least amount of hp,
 * since cowboy doesn't care about distance and we want to cause more death to the enemy team per attack.
 * @param enemy_team  - The team we will choose a victim from.
 * @return - A pointer to a valid victim or nullptr if all members are dead.
 */
Character* SmartTeam :: Locate_cowboy_target (Team* enemy_team) {
    // The victim we will return.
    Character* victim = nullptr;
    // Save the minimum hp.
    double min_hp = numeric_limits <double> :: max();
    // Current hp for each of the warriors in team.
    double hp = 0;
    // Iterate over the enemy team and pick a victim.
    for (size_t i = 0; i < enemy_team -> getWarriorsCount(); i++) {
        // Only if this enemy is alive, check him.
        if (enemy_team -> getWarriors().at(i) -> isAlive()) {
            hp = enemy_team -> getWarriors().at(i)->get_hit_points();
            // Update victim if needed.
            if (hp < min_hp) {
                min_hp = hp;
                victim = enemy_team -> getWarriors().at(i);
            }
        }
    }
    return victim;
}

/**
 * prints all characters in the team (the order doesn't matter).
 */
void SmartTeam :: print (){
    for (size_t i = 0; i < getWarriorsCount(); i++) {
        std::cout << warriors.at(i) -> print() << endl;
    }
}