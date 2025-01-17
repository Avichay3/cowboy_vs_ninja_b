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
const int MAX_WARRIORS = 10;

namespace ariel{
    class Team{
        protected:
            Character *_leader;
            size_t _warriors_count;
            std::vector <Character *> warriors;

        public:
            Team(Character *leader); //constructor
            virtual ~Team(); //destructor for the team object
            void add(Character *);
            virtual void attack(Team *other);
            virtual int stillAlive();
            virtual void print();
            Character* closest_to_leader(Team *team, Character *other) ;
            std::vector<Character* > getWarriors();
            Character* getLeader() const { return _leader; } //inline
            void setLeader(Character* leader) { _leader = leader; } //inline
            size_t getWarriorsCount () const{return _warriors_count;} // inline

    };
}