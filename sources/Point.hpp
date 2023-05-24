#pragma once
namespace ariel{
    class Point{
        double _x;
        double _y;

        public:
        Point(double x, double y); // constructor with two arguments

        double distance(const Point &other) const;

        void print();

        static Point moveTowards(const Point &source, const Point &destination, double distance);

        double getX() const;

        double getY() const;
    };
}