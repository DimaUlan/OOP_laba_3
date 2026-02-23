#include "Pentagon.h"
#include <stdexcept>
#include <cmath>

Pentagon::Pentagon() {
    for (auto& v : vertices) {
        v = Point(0, 0);
    }
}

Pentagon::Pentagon(const std::array<Point, 5>& points) : vertices(points) {
    if (!isValid()) {
        throw std::invalid_argument("Invalid pentagon vertices");
    }
}

Pentagon::Pentagon(const Point& p1, const Point& p2, const Point& p3, const Point& p4, const Point& p5) {
    vertices[0] = p1;
    vertices[1] = p2;
    vertices[2] = p3;
    vertices[3] = p4;
    vertices[4] = p5;
    
    if (!isValid()) {
        throw std::invalid_argument("Invalid pentagon vertices");
    }
}

Pentagon::Pentagon(const Pentagon& other) : vertices(other.vertices) {}

Pentagon::Pentagon(Pentagon&& other) noexcept : vertices(std::move(other.vertices)) {}

Pentagon& Pentagon::operator=(const Pentagon& other) {
    if (this != &other) {
        vertices = other.vertices;
    }
    return *this;
}

Pentagon& Pentagon::operator=(Pentagon&& other) noexcept {
    if (this != &other) {
        vertices = std::move(other.vertices);
    }
    return *this;
}

bool Pentagon::isValid() const {
    for (size_t i = 0; i < 5; ++i) {
        for (size_t j = i + 1; j < 5; ++j) {
            if (vertices[i] == vertices[j]) {
                return false;
            }
        }
    }
    return true;
}

Point Pentagon::getCenter() const {
    double sum_x = 0, sum_y = 0;
    for (const auto& v : vertices) {
        sum_x += v.x;
        sum_y += v.y;
    }
    return Point(sum_x / 5.0, sum_y / 5.0);
}

double Pentagon::getArea() const {
    double sum = 0.0;
    for (int i = 0; i < 5; ++i) {
        const Point& v1 = vertices[i];
        const Point& v2 = vertices[(i + 1) % 5];
        sum += (v1.x * v2.y - v2.x * v1.y);
    }
    return std::abs(sum) / 2.0;
}

bool Pentagon::operator==(const Figure& other) const {
    auto* p = dynamic_cast<const Pentagon*>(&other);
    if (!p) return false;
    
    for (size_t i = 0; i < 5; ++i) {
        if (!(vertices[i] == p->vertices[i])) {
            return false;
        }
    }
    return true;
}

void Pentagon::print(std::ostream& os) const {
    os << "Pentagon (vertices: ";
    for (const auto& v : vertices) {
        os << v << " ";
    }
    os << ")";
}

void Pentagon::read(std::istream& is) {
    for (auto& v : vertices) {
        is >> v;
        if (is.fail()) {
            throw std::runtime_error("Failed to read pentagon vertex");
        }
    }
    
    if (!isValid()) {
        throw std::runtime_error("Invalid pentagon vertices read");
    }
}