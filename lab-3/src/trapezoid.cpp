#include "trapezoid.h"
#include "exceptions.h"
#include <cmath>

Trapezoid::Trapezoid(double x, double y, double top, double bottom, double h)
        : Figure(x, y), topSide(top), bottomSide(bottom), height(h) {
    if (top < 0 || bottom < 0 || h < 0) {
        throw NegativeSideException();
    }
}

std::pair<double, double> Trapezoid::getCenter() const {
    return {x, y};
}

std::vector<std::pair<double, double>> Trapezoid::getVertices() const {
    std::vector<std::pair<double, double>> vertices;

    double halfHeight = height / 2.0;

    vertices.emplace_back(x - topSide / 2, y + halfHeight);
    vertices.emplace_back(x + topSide / 2, y + halfHeight);


    vertices.emplace_back(x + bottomSide / 2, y - halfHeight);
    vertices.emplace_back(x - bottomSide / 2, y - halfHeight);

    return vertices;
}

double Trapezoid::getArea() const {
    return (topSide + bottomSide) * height / 2.0;
}

Figure *Trapezoid::clone() const {
    return new Trapezoid(*this);
}

bool Trapezoid::operator==(const Figure &other) const {
    if (const auto *trap = dynamic_cast<const Trapezoid *>(&other)) {
        return x == trap->x && y == trap->y &&
               topSide == trap->topSide &&
               bottomSide == trap->bottomSide &&
               height == trap->height;
    }
    return false;
}

std::ostream &operator<<(std::ostream &os, const Trapezoid &trap) {
    os << static_cast<const Figure &>(trap)
       << "\nTop side: " << trap.topSide
       << "\nBottom side: " << trap.bottomSide
       << "\nHeight: " << trap.height
       << "\nArea: " << trap.getArea()
       << "\nVertices:";

    auto vertices = trap.getVertices();
    for (size_t i = 0; i < vertices.size(); ++i) {
        os << "\n  " << i + 1 << ": ("
           << vertices[i].first << ", "
           << vertices[i].second << ")";
    }
    return os;
}

std::istream &operator>>(std::istream &is, Trapezoid &trap) {
    operator>>(is, static_cast<Figure &>(trap));
    std::cout << "Enter top side length, bottom side length and height:";
    double top, bottom, height;
    is >> top >> bottom >> height;

    if (top < 0 || bottom < 0 || height < 0) {
        throw NegativeSideException();
    }

    trap.topSide = top;
    trap.bottomSide = bottom;
    trap.height = height;
    return is;
}
