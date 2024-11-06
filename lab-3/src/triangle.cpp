#include "triangle.h"
#include "exceptions.h"
#include <cmath>

Triangle::Triangle(double x, double y, double s)
        : Figure(x, y), side(s) {}

double Triangle::getHeight() const {
    return side * std::sqrt(3.0) / 2.0;
}

std::pair<double, double> Triangle::getCenter() const {
    return {x, y};
}

std::vector<std::pair<double, double>> Triangle::getVertices() const {
    std::vector<std::pair<double, double>> vertices;
    double r = side / (2 * std::sqrt(3));

    vertices.emplace_back(x, y + r * std::sqrt(3));
    vertices.emplace_back(x - side / 2, y - r);
    vertices.emplace_back(x + side / 2, y - r);

    return vertices;
}

double Triangle::getArea() const {
    return 0.5 * side * getHeight();
}

Figure *Triangle::clone() const {
    return new Triangle(*this);
}

bool Triangle::operator==(const Figure &other) const {
    if (const auto *tr = dynamic_cast<const Triangle *>(&other)) {
        return x == tr->x && y == tr->y && side == tr->side;
    }
    return false;
}

std::ostream &operator<<(std::ostream &os, const Triangle &tr) {
    os << static_cast<const Figure &>(tr)
       << "\nSide: " << tr.side
       << "\nHeight: " << tr.getHeight()
       << "\nArea: " << tr.getArea()
       << "\nVertices:";

    auto vertices = tr.getVertices();
    for (size_t i = 0; i < vertices.size(); ++i) {
        os << "\n  " << i + 1 << ": ("
           << vertices[i].first << ", "
           << vertices[i].second << ")";
    }
    return os;
}

std::istream &operator>>(std::istream &is, Triangle &tr) {
    operator>>(is, static_cast<Figure &>(tr));
    std::cout << "Enter side length:";
    double side;
    is >> side;

    if (side < 0) {
        throw NegativeSideException();
    }

    tr.side = side;
    return is;
}