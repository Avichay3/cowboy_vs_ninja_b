#include <iostream>
#include "sources/Team.hpp"

using namespace ariel;

auto multi_attack = [](int n, Team &attacker, Team &defender)
{
    for (int i = 0; i < n; i++)
    {
        if (defender.stillAlive())
        {
            attacker.attack(&defender);
        }
    }
};

int main()
{
    // Create character locations
    Point p1(10.5, 7.2);
    Point p2(15.8, 12.1);
    Point p3(20.3, 9.6);
    Point p4(5.2, 3.9);
    try{
        // Create characters
        Character *leader = new Cowboy("Avichay", p1);
        Character *warrior1 = new TrainedNinja("Orel", p2);
        Character *warrior2 = new Cowboy("David", p3);
        Character *warrior3 = new OldNinja("Noam", p4);

        // Create a team and add characters to it
        Team team(leader);
        team.add(warrior1);
        team.add(warrior2);
        team.add(warrior3);
        // Print the initial team
        std::cout << "Initial Team:" << std::endl;
        team.print();

        // Move the leader character
        Point newLocation(12.8, 9.1);
        leader->getLocation().moveTowards(leader->getLocation(), newLocation, 2.5);

        // Attack another team
        Team enemyTeam(new Cowboy("Tohar", Point(5.6, 7.1)));
        enemyTeam.add(new YoungNinja("Dov", Point(8.7, 5.4)));
        enemyTeam.add(new Cowboy("Yael", Point(17.2, 13.5)));

        // Print the updated teams
        std::cout << "Updated Team:" << std::endl;
        team.print();

        std::cout << "Enemy Team:" << std::endl;
        enemyTeam.print();

        // team attack enemyTeam 3 times
        multi_attack(3, team, enemyTeam);
        // Print the updated teams
        std::cout << "Updated Team:" << std::endl;
        team.print();

        std::cout << "Enemy Team:" << std::endl;
        enemyTeam.print();

        // Check if enemy characters are alive
        std::cout << "Checking if enemy characters are alive..." << std::endl;
        for (auto enemy : enemyTeam.getWarriors()){
            if (enemy->isAlive()){
                std::cout << enemy->getName() << " is alive." << std::endl;
            }
            else{
                std::cout << enemy->getName() << " is dead." << std::endl;
            }
        }
    }
    catch (const std::exception &e){
        std::cout << "An exception occurred: " << e.what() << std::endl;
    }

    return 0;
}

