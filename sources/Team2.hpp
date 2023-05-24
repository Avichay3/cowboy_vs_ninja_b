#pragma once
#include "Team.hpp"

const int MAX_WARRIORS = 10;

namespace ariel{
    class Team2 : public Team{ //inherit from Team class

        private:
            Character *_leader;
            std::vector <Character *> warriors{10};

        public:

            Team2(Character *leader);

            void attack(Team *other) override;

            void print() override;

            int stillAlive() override;

    };
}