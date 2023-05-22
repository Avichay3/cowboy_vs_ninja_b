#pragma once
#include "Character.hpp"

namespace ariel{
    class Cowboy : public Character{ // inherit

        int _num_of_bullets;

        public:
            Cowboy(std::string name, Point location); //constructor

            void shoot(Character *other);

            bool hasBullets()const;

            void reload();

            std::string print();

    };
}