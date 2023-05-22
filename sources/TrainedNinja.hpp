#pragma once
#include "Ninja.hpp"

namespace ariel{
    class TrainedNinja : public Ninja{

        public:
            TrainedNinja(std::string name, Point location, int hit_points, int speed);
            TrainedNinja(std::string name, Point location); //another constructor


    };
}