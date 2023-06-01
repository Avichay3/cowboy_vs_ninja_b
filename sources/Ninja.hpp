#pragma once
#include "Character.hpp"

namespace ariel{
    class Ninja : public Character{ // inheritence

        protected:
            int _speed;

        public:
            Ninja(std::string name, Point location, int hit_points, int speed); //constructor
            Ninja(std::string name, Point location); // another one constructor

            void move(Character *other);

            void slash(Character *other);

            std::string print() override;

            int getSpeed () const;

    };
}