#include "TrainedNinja.hpp"
using namespace ariel;

TrainedNinja::TrainedNinja(std::string name, Point location, int hit_points, int speed) :
Ninja(name, location , 120, 12){}

TrainedNinja::TrainedNinja(std::string name, Point location) : Ninja(name, location){}

