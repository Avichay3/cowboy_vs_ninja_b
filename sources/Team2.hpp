#pragma once
#include "Team.hpp"



namespace ariel{
    class Team2 : public Team{ //inherit from Team class

        public:

            Team2(Character *leader);

            void attack(Team *other) override;

            void print() override;

            int stillAlive() override;

    };
}