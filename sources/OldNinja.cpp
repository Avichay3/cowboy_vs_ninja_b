#include "OldNinja.hpp"
#include "Ninja.hpp"
using namespace ariel;

OldNinja::OldNinja(std::string name, Point location, int hit_points, int speed) :  /// first constructor
Ninja(name, location, 150, 8){}

OldNinja::OldNinja(std::string Name, Point location): Ninja(Name, location){} // another constructor

