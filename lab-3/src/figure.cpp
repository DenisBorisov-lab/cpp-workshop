#include "figure.h"

Figure::Figure(double x, double y) : x(x), y(y) {}

std::ostream& operator<<(std::ostream& os, const Figure& fig) {
    os << "Center: (" << fig.x << ", " << fig.y << ")";
    return os;
}

std::istream& operator>>(std::istream& is, Figure& fig) {
    std::cout << "Enter center coordinates (x y):";
    is >> fig.x >> fig.y;
    return is;
}