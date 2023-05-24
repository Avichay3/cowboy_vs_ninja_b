#pragma once
#include "Ninja.hpp"

namespace ariel{
    class OldNinja : public Ninja{ //inherit from Ninja class

        public:
            // OldNinja(std::string name, Point location, int hit_points, int speed);
            OldNinja(std::string Name, Point location);
    };
}