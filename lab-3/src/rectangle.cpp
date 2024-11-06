#include "rectangle.h"
#include "exceptions.h"
#include <cmath>

Rectangle::Rectangle(double x, double y, double w, double h)
        : Figure(x, y), width(w), height(h) {
    if (w < 0 || h < 0) {
        throw NegativeSideException();
    }
}

std::pair<double, double> Rectangle::getCenter() const {
    return {x, y};
}

std::vector<std::pair<double, double>> Rectangle::getVertices() const {
    std::vector<std::pair<double, double>> vertices;
    double half_width = width / 2;
    double half_height = height / 2;

    vertices.emplace_back(x - half_width, y + half_height);
    vertices.emplace_back(x + half_width, y + half_height);
    vertices.emplace_back(x + half_width, y - half_height);
    vertices.emplace_back(x - half_width, y - half_height);

    return vertices;
}

double Rectangle::getArea() const {
    return width * height;
}

Figure *Rectangle::clone() const {
    return new Rectangle(*this);
}

bool Rectangle::operator==(const Figure &other) const {
    if (const auto *rect = dynamic_cast<const Rectangle *>(&other)) {
        return x == rect->x && y == rect->y &&
               width == rect->width && height == rect->height;
    }
    return false;
}

std::ostream &operator<<(std::ostream &os, const Rectangle &rect) {
    os << static_cast<const Figure &>(rect)
       << "\nWidth: " << rect.width
       << "\nHeight: " << rect.height
       << "\nArea: " << rect.getArea()
       << "\nVertices:";

    auto vertices = rect.getVertices();
    for (size_t i = 0; i < vertices.size(); ++i) {
        os << "\n  " << i + 1 << ": ("
           << vertices[i].first << ", "
           << vertices[i].second << ")";
    }
    return os;
}

std::istream &operator>>(std::istream &is, Rectangle &rect) {
    operator>>(is, static_cast<Figure &>(rect));
    std::cout << "Enter width and height:";
    double w, h;
    is >> w >> h;

    if (w < 0 || h < 0) {
        throw NegativeSideException();
    }

    rect.width = w;
    rect.height = h;
    return is;
}
