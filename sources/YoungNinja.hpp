#pragma once
#include "Ninja.hpp"

namespace ariel{
    class YoungNinja : public Ninja{

        public:
            YoungNinja(std::string name, Point location, int hit_points, int speed);
            YoungNinja(std::string name, Point location);



    };
}