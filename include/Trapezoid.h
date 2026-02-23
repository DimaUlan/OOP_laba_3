#ifndef TRAPEZOID_H
#define TRAPEZOID_H

#include "Figure.h"

class Trapezoid : public Figure {
private:
    Point p1, p2, p3, p4;

public:

    Trapezoid();
    Trapezoid(const Point& a, const Point& b, const Point& c, const Point& d);

    Trapezoid(const Trapezoid& other);
    Trapezoid(Trapezoid&& other) noexcept;

    ~Trapezoid() override = default;

    Trapezoid& operator=(const Trapezoid& other);
    Trapezoid& operator=(Trapezoid&& other) noexcept;

    bool operator==(const Figure& other) const override;

    Point getCenter() const override;
    void print(std::ostream& os) const override;
    void read(std::istream& is) override;
    double area() const override;
    Figure* clone() const override {
        return new Trapezoid(*this);
    }
};

#endif