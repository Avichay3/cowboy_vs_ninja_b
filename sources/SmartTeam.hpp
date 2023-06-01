#pragma once
#include "Team.hpp"
#include <vector>
#include "Team.hpp"
#include <vector>

namespace ariel
{
    class SmartTeam : public Team
    {
    public:
        SmartTeam(Character *character);
        ~SmartTeam() = default;
        void attack(Team *enemies) override;
        std::vector<Character*> findClosestCharacters(Team* attackerTeam, Team* enemyTeam);
    };
}