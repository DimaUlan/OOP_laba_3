#include "Trapezoid.h"
#include <iostream>
#include <cmath>

Trapezoid::Trapezoid()
    : p1(), p2(), p3(), p4() {}

Trapezoid::Trapezoid(const Point& a, const Point& b, const Point& c, const Point& d)
    : p1(a), p2(b), p3(c), p4(d) {}

Trapezoid::Trapezoid(const Trapezoid& other)
    : p1(other.p1), p2(other.p2), p3(other.p3), p4(other.p4) {}

Trapezoid::Trapezoid(Trapezoid&& other) noexcept
    : p1(std::move(other.p1)), p2(std::move(other.p2)), p3(std::move(other.p3)), p4(std::move(other.p4)) {}

Trapezoid& Trapezoid::operator=(const Trapezoid& other) {
    if (this != &other) {
        p1 = other.p1;
        p2 = other.p2;
        p3 = other.p3;
        p4 = other.p4;
    }
    return *this;
}

Trapezoid& Trapezoid::operator=(Trapezoid&& other) noexcept {
    if (this != &other) {
        p1 = std::move(other.p1);
        p2 = std::move(other.p2);
        p3 = std::move(other.p3);
        p4 = std::move(other.p4);
    }
    return *this;
}

bool Trapezoid::operator==(const Figure& other) const {
    const Trapezoid* p = dynamic_cast<const Trapezoid*>(&other);
    if (!p) return false;
    return (p1 == p->p1) && (p2 == p->p2) && (p3 == p->p3) && (p4 == p->p4);
}

Point Trapezoid::getCenter() const {
    return Point{
        (p1.x + p2.x + p3.x + p4.x) / 4.0,
        (p1.y + p2.y + p3.y + p4.y) / 4.0
    };
}

void Trapezoid::print(std::ostream& os) const {
    os << "Трапеция вершины:\n";
    os << "(" << p1.x << ", " << p1.y << ")\n";
    os << "(" << p2.x << ", " << p2.y << ")\n";
    os << "(" << p3.x << ", " << p3.y << ")\n";
    os << "(" << p4.x << ", " << p4.y << ")\n";
}

void Trapezoid::read(std::istream& is) {
    is >> p1.x >> p1.y >> p2.x >> p2.y >> p3.x >> p3.y >> p4.x >> p4.y;
}

double Trapezoid::area() const {
    double sum = 0.0;
    const Point vertices[4] = {p1, p2, p3, p4};
    for (int i = 0; i < 4; ++i) {
        const Point& v1 = vertices[i];
        const Point& v2 = vertices[(i + 1) % 4];
        sum += v1.x * v2.y - v2.x * v1.y;
    }
    return std::abs(sum) / 2.0;
}