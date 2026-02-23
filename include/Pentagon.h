#ifndef PENTAGON_H
#define PENTAGON_H

#include "Figure.h"
#include <array>

class Pentagon : public Figure {
private:
    std::array<Point, 5> vertices;
    bool isValid() const;

public:
    Pentagon();
    explicit Pentagon(const std::array<Point, 5>& points);
    Pentagon(const Point& p1, const Point& p2, const Point& p3, const Point& p4, const Point& p5);
    
    // Явное определение конструкторов (НЕ =default)
    Pentagon(const Pentagon& other);
    Pentagon& operator=(const Pentagon& other);
    
    Pentagon(Pentagon&& other) noexcept;
    Pentagon& operator=(Pentagon&& other) noexcept;
    
    ~Pentagon() override = default;
    
    Point getCenter() const override;
    double getArea() const override;
    operator double() const override { return getArea(); }
    bool operator==(const Figure& other) const override;
    Figure* clone() const override { return new Pentagon(*this); }

protected:
    void print(std::ostream& os) const override;
    void read(std::istream& is) override;
};

#endif