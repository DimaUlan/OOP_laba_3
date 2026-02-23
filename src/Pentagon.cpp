#include "Pentagon.h"
#include <iostream>
#include <cmath>

Pentagon::Pentagon()
    : p1{0.0, 0.0}, p2{0.0, 0.0}, p3{0.0, 0.0}, p4{0.0, 0.0}, p5{0.0, 0.0} {}

Pentagon::Pentagon(const Point points[5])
    : p1(points[0]), p2(points[1]), p3(points[2]), p4(points[3]), p5(points[4]) {}

Pentagon::Pentagon(const Point& p1, const Point& p2, const Point& p3, const Point& p4, const Point& p5)
    : p1(p1), p2(p2), p3(p3), p4(p4), p5(p5) {}

Pentagon::Pentagon(const Pentagon& other)
    : p1(other.p1), p2(other.p2), p3(other.p3), p4(other.p4), p5(other.p5) {}

Pentagon::Pentagon(Pentagon&& other) noexcept
    : p1(std::move(other.p1)),
      p2(std::move(other.p2)),
      p3(std::move(other.p3)),
      p4(std::move(other.p4)),
      p5(std::move(other.p5)) {}


Pentagon& Pentagon::operator=(const Pentagon& other) {
    if (this != &other) {
        p1 = other.p1;
        p2 = other.p2;
        p3 = other.p3;
        p4 = other.p4;
        p5 = other.p5;
    }
    return *this;
}

Pentagon& Pentagon::operator=(Pentagon&& other) noexcept {
    if (this != &other) {
        p1 = std::move(other.p1);
        p2 = std::move(other.p2);
        p3 = std::move(other.p3);
        p4 = std::move(other.p4);
        p5 = std::move(other.p5);
    }
    return *this;
}

bool Pentagon::operator==(const Figure& other) const {
    const Pentagon* p = dynamic_cast<const Pentagon*>(&other);
    if (!p) return false;
    
    return (p1 == p->p1) && (p2 == p->p2) && (p3 == p->p3) &&
           (p4 == p->p4) && (p5 == p->p5);
}

Point Pentagon::getCenter() const {
    double sum_x = p1.x + p2.x + p3.x + p4.x + p5.x;
    double sum_y = p1.y + p2.y + p3.y + p4.y + p5.y;
    return Point{sum_x / 5.0, sum_y / 5.0};
}

void Pentagon::print(std::ostream& os) const {
    os << "Пятиугольник вершины: ";
    os << "(" << p1.x << ", " << p1.y << ") ";
    os << "(" << p2.x << ", " << p2.y << ") ";
    os << "(" << p3.x << ", " << p3.y << ") ";
    os << "(" << p4.x << ", " << p4.y << ") ";
    os << "(" << p5.x << ", " << p5.y << ")\n";
}

void Pentagon::read(std::istream& is) {
    is >> p1.x >> p1.y;
    is >> p2.x >> p2.y;
    is >> p3.x >> p3.y;
    is >> p4.x >> p4.y;
    is >> p5.x >> p5.y;
}

double Pentagon::area() const {
    const Point vertices[5] = {p1, p2, p3, p4, p5};
    
    double sum = 0.0;
    for (int i = 0; i < 5; ++i) {
        const Point& v1 = vertices[i];
        const Point& v2 = vertices[(i + 1) % 5];
        sum += (v1.x * v2.y - v2.x * v1.y);
    }
    return std::abs(sum) / 2.0;
}
