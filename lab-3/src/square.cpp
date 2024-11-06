#include "square.h"
#include "exceptions.h"
#include <cmath>

Square::Square(double x, double y, double s)
        : Figure(x, y), side(s) {
    if (s < 0) {
        throw NegativeSideException();
    }
}

std::pair<double, double> Square::getCenter() const {
    return {x, y};
}

std::vector<std::pair<double, double>> Square::getVertices() const {
    std::vector<std::pair<double, double>> vertices;
    double half_side = side / 2;

    vertices.emplace_back(x - half_side, y + half_side);
    vertices.emplace_back(x + half_side, y + half_side);
    vertices.emplace_back(x + half_side, y - half_side);
    vertices.emplace_back(x - half_side, y - half_side);

    return vertices;
}

double Square::getArea() const {
    return side * side;
}

Figure *Square::clone() const {
    return new Square(*this);
}

bool Square::operator==(const Figure &other) const {
    if (const auto *sq = dynamic_cast<const Square *>(&other)) {
        return x == sq->x && y == sq->y && side == sq->side;
    }
    return false;
}

std::ostream &operator<<(std::ostream &os, const Square &sq) {
    os << static_cast<const Figure &>(sq)
       << "\nSide length: " << sq.side
       << "\nArea: " << sq.getArea()
       << "\nVertices:";

    auto vertices = sq.getVertices();
    for (size_t i = 0; i < vertices.size(); ++i) {
        os << "\n  " << i + 1 << ": ("
           << vertices[i].first << ", "
           << vertices[i].second << ")";
    }
    return os;
}

std::istream &operator>>(std::istream &is, Square &sq) {
    operator>>(is, static_cast<Figure &>(sq));
    std::cout << "Enter side length:";
    double side;
    is >> side;

    if (side < 0) {
        throw NegativeSideException();
    }

    sq.side = side;
    return is;
}
