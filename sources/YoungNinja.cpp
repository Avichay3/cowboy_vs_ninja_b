#include "YoungNinja.hpp"
using namespace ariel;

YoungNinja::YoungNinja(std::string name, Point location, int hit_points, int speed) : //initialization list
Ninja(name, location, 100, 14){}

YoungNinja::YoungNinja(std::string name, Point location) : Ninja(name,location){}
