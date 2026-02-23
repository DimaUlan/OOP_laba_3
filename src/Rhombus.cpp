#include "Rhombus.h"
#include <stdexcept>
#include <cmath>

Rhombus::Rhombus() {
    for (auto& v : vertices) {
        v = Point(0, 0);
    }
}

Rhombus::Rhombus(const std::array<Point, 4>& points) : vertices(points) {
    if (!isValid()) {
        throw std::invalid_argument("Invalid rhombus vertices");
    }
}

Rhombus::Rhombus(const Point& p1, const Point& p2, const Point& p3, const Point& p4) {
    vertices[0] = p1;
    vertices[1] = p2;
    vertices[2] = p3;
    vertices[3] = p4;
    
    if (!isValid()) {
        throw std::invalid_argument("Invalid rhombus vertices");
    }
}

Rhombus::Rhombus(const Rhombus& other) : vertices(other.vertices) {}

Rhombus::Rhombus(Rhombus&& other) noexcept : vertices(std::move(other.vertices)) {}

Rhombus& Rhombus::operator=(const Rhombus& other) {
    if (this != &other) {
        vertices = other.vertices;
    }
    return *this;
}

Rhombus& Rhombus::operator=(Rhombus&& other) noexcept {
    if (this != &other) {
        vertices = std::move(other.vertices);
    }
    return *this;
}

bool Rhombus::isValid() const {
    auto sideLength = [](const Point& a, const Point& b) {
        double dx = a.x - b.x;
        double dy = a.y - b.y;
        return std::sqrt(dx*dx + dy*dy);
    };
    
    double s01 = sideLength(vertices[0], vertices[1]);
    double s12 = sideLength(vertices[1], vertices[2]);
    double s23 = sideLength(vertices[2], vertices[3]);
    double s30 = sideLength(vertices[3], vertices[0]);
    
    return (std::abs(s01 - s12) == 0 && 
            std::abs(s12 - s23) == 0 && 
            std::abs(s23 - s30) == 0);
}

Point Rhombus::getCenter() const {
    double sum_x = 0, sum_y = 0;
    for (const auto& v : vertices) {
        sum_x += v.x;
        sum_y += v.y;
    }
    return Point(sum_x / 4.0, sum_y / 4.0);
}

double Rhombus::getArea() const {
    double dx1 = vertices[2].x - vertices[0].x;
    double dy1 = vertices[2].y - vertices[0].y;
    double dx2 = vertices[3].x - vertices[1].x;
    double dy2 = vertices[3].y - vertices[1].y;
    
    return 0.5 * std::abs(dx1 * dy2 - dy1 * dx2);
}

bool Rhombus::operator==(const Figure& other) const {
    auto* r = dynamic_cast<const Rhombus*>(&other);
    if (!r) return false;
    
    for (size_t i = 0; i < 4; ++i) {
        if (!(vertices[i] == r->vertices[i])) {
            return false;
        }
    }
    return true;
}

void Rhombus::print(std::ostream& os) const {
    os << "Rhombus (vertices: ";
    for (const auto& v : vertices) {
        os << v << " ";
    }
    os << ")";
}

void Rhombus::read(std::istream& is) {
    for (auto& v : vertices) {
        is >> v;
        if (is.fail()) {
            throw std::runtime_error("Failed to read rhombus vertex");
        }
    }
    
    if (!isValid()) {
        throw std::runtime_error("Invalid rhombus vertices read");
    }
}