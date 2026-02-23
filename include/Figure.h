#ifndef FIGURE_H
#define FIGURE_H

#include <iostream>
#include <cmath>

struct Point {
    double x, y;
    Point(double _x=0, double _y=0) : x(_x), y(_y) {}
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

class Figure {
public:
    virtual ~Figure() = default;
    virtual Point getCenter() const = 0;
    virtual double area() const = 0;
    virtual void print(std::ostream& os) const = 0;
    virtual void read(std::istream& is) = 0;
    virtual Figure* clone() const = 0;
    friend std::ostream& operator<<(std::ostream& os, const Figure& fig);
    friend std::istream& operator>>(std::istream& is, Figure& fig);
    virtual bool operator==(const Figure& other) const { return false; }
    virtual operator double() const { return area(); }
};

#endif