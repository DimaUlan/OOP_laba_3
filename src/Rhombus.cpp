#include "Rhombus.h"
#include <iostream>
#include <cmath>
#include <stdexcept>

Rhombus::Rhombus()
    : p1(), p2(), p3(), p4() {}

Rhombus::Rhombus(const Point& _p1, const Point& _p2, const Point& _p3, const Point& _p4)
    : p1(_p1), p2(_p2), p3(_p3), p4(_p4) {}

Rhombus::Rhombus(const Rhombus& other)
    : p1(other.p1), p2(other.p2), p3(other.p3), p4(other.p4) {}

Rhombus::Rhombus(Rhombus&& other) noexcept
    : p1(std::move(other.p1)),
      p2(std::move(other.p2)),
      p3(std::move(other.p3)),
      p4(std::move(other.p4)) {}

Rhombus& Rhombus::operator=(const Rhombus& other) {
    if (this != &other) {
        p1 = other.p1;
        p2 = other.p2;
        p3 = other.p3;
        p4 = other.p4;
    }
    return *this;
}

Rhombus& Rhombus::operator=(Rhombus&& other) noexcept {
    if (this != &other) {
        p1 = std::move(other.p1);
        p2 = std::move(other.p2);
        p3 = std::move(other.p3);
        p4 = std::move(other.p4);
    }
    return *this;
}

bool Rhombus::operator==(const Figure& other) const {
    const Rhombus* r = dynamic_cast<const Rhombus*>(&other);
    if (!r) return false;

    return (p1 == r->p1) && (p2 == r->p2) && (p3 == r->p3) && (p4 == r->p4);
}

Point Rhombus::getCenter() const {
    double sum_x = p1.x + p2.x + p3.x + p4.x;
    double sum_y = p1.y + p2.y + p3.y + p4.y;
    return Point{sum_x / 4.0, sum_y / 4.0};
}

void Rhombus::print(std::ostream& os) const {
    os << "Ромб вершины: ";
    os << "(" << p1.x << ", " << p1.y << ") ";
    os << "(" << p2.x << ", " << p2.y << ") ";
    os << "(" << p3.x << ", " << p3.y << ") ";
    os << "(" << p4.x << ", " << p4.y << ")\n";
}

void Rhombus::read(std::istream& is) {
    is >> p1.x >> p1.y;
    is >> p2.x >> p2.y;
    is >> p3.x >> p3.y;
    is >> p4.x >> p4.y;
}

double Rhombus::area() const {
    double dx1 = p3.x - p1.x;
    double dy1 = p3.y - p1.y;
    double dx2 = p4.x - p2.x;
    double dy2 = p4.y - p2.y;

    double cross = std::abs(dx1 * dy2 - dy1 * dx2);

    return 0.5 * cross;
}

Rhombus::operator double() const {
    return area();
}
