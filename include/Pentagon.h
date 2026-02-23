#ifndef PENTAGON_H
#define PENTAGON_H

#include "Figure.h"

class Pentagon : public Figure {
private:
    Point p1, p2, p3, p4, p5;

public:
    Pentagon();
    explicit Pentagon(const Point points[5]);
    Pentagon(const Point& p1, const Point& p2, const Point& p3, const Point& p4, const Point& p5);

    Pentagon(const Pentagon& other);
    Pentagon(Pentagon&& other) noexcept;

    ~Pentagon() override = default;

    Pentagon& operator=(const Pentagon& other);
    Pentagon& operator=(Pentagon&& other) noexcept;

    bool operator==(const Figure& other) const override;

    Point getCenter() const override;
    void print(std::ostream& os) const override;
    void read(std::istream& is) override;
    double area() const override;

    Figure* clone() const override {
        return new Pentagon(*this);
    }

    operator double() const override {
        return area();
    }
};

#endif
