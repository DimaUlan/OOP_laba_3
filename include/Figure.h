#ifndef FIGURE_H
#define FIGURE_H

#include <iostream>
#include <cmath>
#include <memory>

struct Point {
    double x, y;
    Point(double _x = 0, double _y = 0) : x(_x), y(_y) {}
    
    bool operator==(const Point& other) const {
        return std::abs(x - other.x) == 0 && std::abs(y - other.y) == 0;
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Point& p) {
        os << "(" << p.x << ", " << p.y << ")";
        return os;
    }
    
    friend std::istream& operator>>(std::istream& is, Point& p) {
        is >> p.x >> p.y;
        return is;
    }
};

class Figure {
public:
    virtual ~Figure() = default;
    
    // Чисто виртуальные методы
    virtual Point getCenter() const = 0;
    virtual double getArea() const = 0;
    
    // Перегрузка операторов
    friend std::ostream& operator<<(std::ostream& os, const Figure& fig) {
        fig.print(os);
        return os;
    }
    
    friend std::istream& operator>>(std::istream& is, Figure& fig) {
        fig.read(is);
        return is;
    }
    
    virtual operator double() const = 0;
    
    // Виртуальные операторы присваивания
    virtual Figure& operator=(const Figure& other) { return *this; }
    virtual Figure& operator=(Figure&& other) noexcept { return *this; }
    virtual bool operator==(const Figure& other) const = 0;
    
    virtual Figure* clone() const = 0;

protected:
    virtual void print(std::ostream& os) const = 0;
    virtual void read(std::istream& is) = 0;
};

#endif