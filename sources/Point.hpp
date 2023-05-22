#pragma once
namespace ariel{
    class Point{
        double _x;
        double _y;

        public:
        Point(double x, double y); // constructor with two arguments
        double distance(Point &other);
        void print();
        Point moveTowards(Point &source, Point &destination, double distance);
    };
}