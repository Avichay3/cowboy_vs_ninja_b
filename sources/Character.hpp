#pragma once
#include "Point.hpp"
#include <iostream>


namespace ariel{
    class Character{
    private:
        Point &_location;
        int _hit_points;
        std::string _name;
        bool _is_in_team_already = false;


    public:
        Character(std::string name, Point &location, int hit_points); //constructor with all parameters inside

        Character(std::string name, Point &location);

        bool isAlive();

        double distance(Character *other);

        virtual void hit(int); //virtual for the ability to ovveride it

        std::string getName() const; 

        int get_hit_points() const;

        Point getLocation() const;

        virtual std::string print(); //virtual for the ability to ovveride it

        virtual bool IsInTeamAlready();

        virtual void setInTeam(bool);
        


    };
}