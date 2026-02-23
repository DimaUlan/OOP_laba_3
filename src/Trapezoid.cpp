#include "Trapezoid.h"
#include <stdexcept>
#include <cmath>

Trapezoid::Trapezoid() {
    for (auto& v : vertices) {
        v = Point(0, 0);
    }
}

Trapezoid::Trapezoid(const std::array<Point, 4>& points) : vertices(points) {
    if (!isValid()) {
        throw std::invalid_argument("Invalid trapezoid vertices");
    }
}

Trapezoid::Trapezoid(const Point& p1, const Point& p2, const Point& p3, const Point& p4) {
    vertices[0] = p1;
    vertices[1] = p2;
    vertices[2] = p3;
    vertices[3] = p4;
    
    if (!isValid()) {
        throw std::invalid_argument("Invalid trapezoid vertices");
    }
}

// Явное определение конструктора копирования
Trapezoid::Trapezoid(const Trapezoid& other) : vertices(other.vertices) {}

// Явное определение конструктора перемещения
Trapezoid::Trapezoid(Trapezoid&& other) noexcept : vertices(std::move(other.vertices)) {}

Trapezoid& Trapezoid::operator=(const Trapezoid& other) {
    if (this != &other) {
        vertices = other.vertices;
    }
    return *this;
}

Trapezoid& Trapezoid::operator=(Trapezoid&& other) noexcept {
    if (this != &other) {
        vertices = std::move(other.vertices);
    }
    return *this;
}

bool Trapezoid::isValid() const {
    auto isParallel = [](const Point& a1, const Point& a2, const Point& b1, const Point& b2) {
        double dx1 = a2.x - a1.x;
        double dy1 = a2.y - a1.y;
        double dx2 = b2.x - b1.x;
        double dy2 = b2.y - b1.y;
        
        return std::abs(dx1 * dy2 - dy1 * dx2) == 0;
    };
    
    return (isParallel(vertices[0], vertices[1], vertices[2], vertices[3]) ||
            isParallel(vertices[1], vertices[2], vertices[3], vertices[0]));
}

Point Trapezoid::getCenter() const {
    double sum_x = 0, sum_y = 0;
    for (const auto& v : vertices) {
        sum_x += v.x;
        sum_y += v.y;
    }
    return Point(sum_x / 4.0, sum_y / 4.0);
}

double Trapezoid::getArea() const {
    double sum = 0.0;
    for (int i = 0; i < 4; ++i) {
        const Point& v1 = vertices[i];
        const Point& v2 = vertices[(i + 1) % 4];
        sum += (v1.x * v2.y - v2.x * v1.y);
    }
    return std::abs(sum) / 2.0;
}

bool Trapezoid::operator==(const Figure& other) const {
    auto* t = dynamic_cast<const Trapezoid*>(&other);
    if (!t) return false;
    
    for (size_t i = 0; i < 4; ++i) {
        if (!(vertices[i] == t->vertices[i])) {
            return false;
        }
    }
    return true;
}

void Trapezoid::print(std::ostream& os) const {
    os << "Trapezoid (vertices: ";
    for (const auto& v : vertices) {
        os << v << " ";
    }
    os << ")";
}

void Trapezoid::read(std::istream& is) {
    for (auto& v : vertices) {
        is >> v;
        if (is.fail()) {
            throw std::runtime_error("Failed to read trapezoid vertex");
        }
    }
    
    if (!isValid()) {
        throw std::runtime_error("Invalid trapezoid vertices read");
    }
}