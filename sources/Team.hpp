#pragma once
/*need to include all classes because it can be all the warriors*/
#include "Character.hpp"
#include "Ninja.hpp"
#include "TrainedNinja.hpp"
#include "OldNinja.hpp"
#include "YoungNinja.hpp"
#include "Cowboy.hpp"
#include "Point.hpp"
#include <vector> // for the arrayList that gonna hold up to 10 warriors

namespace ariel{
    class Team{
        Character *_leader;
        std::vector <Character *> warriors{10};

        public:
            Team(Character *leader); //constructor
            ~Team(); //destructor for the team object
            void add(Character *);
            virtual void attack(Team *other);
            virtual int stillAlive();
            virtual void print();



    };
}