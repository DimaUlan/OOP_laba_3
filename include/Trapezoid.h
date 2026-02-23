#ifndef TRAPEZOID_H
#define TRAPEZOID_H

#include "Figure.h"
#include <array>

class Trapezoid : public Figure {
private:
    std::array<Point, 4> vertices;
    bool isValid() const;

public:
    Trapezoid();
    explicit Trapezoid(const std::array<Point, 4>& points);
    Trapezoid(const Point& p1, const Point& p2, const Point& p3, const Point& p4);
    
    // Явное определение конструкторов (НЕ =default и БЕЗ override)
    Trapezoid(const Trapezoid& other);
    Trapezoid& operator=(const Trapezoid& other);
    
    Trapezoid(Trapezoid&& other) noexcept;
    Trapezoid& operator=(Trapezoid&& other) noexcept;
    
    ~Trapezoid() override = default;
    
    Point getCenter() const override;
    double getArea() const override;
    operator double() const override { return getArea(); }
    bool operator==(const Figure& other) const override;
    Figure* clone() const override { return new Trapezoid(*this); }

protected:
    void print(std::ostream& os) const override;
    void read(std::istream& is) override;
};

#endif