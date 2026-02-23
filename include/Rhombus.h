#ifndef RHOMBUS_H
#define RHOMBUS_H

#include "Figure.h"

class Rhombus : public Figure {
private:
    Point p1, p2, p3, p4;

public:
    Rhombus();
    Rhombus(const Point& _p1, const Point& _p2, const Point& _p3, const Point& _p4);

    Rhombus(const Rhombus& other);
    Rhombus(Rhombus&& other) noexcept;

    ~Rhombus() override = default;

    Rhombus& operator=(const Rhombus& other);
    Rhombus& operator=(Rhombus&& other) noexcept;

    bool operator==(const Figure& other) const override;

    Point getCenter() const override;
    void print(std::ostream& os) const override;
    void read(std::istream& is) override;
    double area() const override;

    Figure* clone() const override {
        return new Rhombus(*this);
    }

    operator double() const override;
};

#endif
