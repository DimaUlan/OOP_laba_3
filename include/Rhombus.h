#ifndef RHOMBUS_H
#define RHOMBUS_H

#include "Figure.h"
#include <array>

class Rhombus : public Figure {
private:
    std::array<Point, 4> vertices;
    bool isValid() const;

public:
    Rhombus();
    explicit Rhombus(const std::array<Point, 4>& points);
    Rhombus(const Point& p1, const Point& p2, const Point& p3, const Point& p4);
    
    // Явное определение конструкторов
    Rhombus(const Rhombus& other);
    Rhombus& operator=(const Rhombus& other);
    
    Rhombus(Rhombus&& other) noexcept;
    Rhombus& operator=(Rhombus&& other) noexcept;
    
    ~Rhombus() override = default;
    
    Point getCenter() const override;
    double getArea() const override;
    operator double() const override { return getArea(); }
    bool operator==(const Figure& other) const override;
    Figure* clone() const override { return new Rhombus(*this); }

protected:
    void print(std::ostream& os) const override;
    void read(std::istream& is) override;
};

#endif