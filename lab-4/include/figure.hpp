#ifndef FIGURE_HPP
#define FIGURE_HPP

#include <memory>
#include <vector>
#include "point.hpp"

template<Scalar T>
class Figure {
protected:
    Point<T> center;

public:
    Figure() = default;

    explicit Figure(const Point<T> &centerPoint) : center(centerPoint) {}

    virtual ~Figure() = default;

    Figure(const Figure &) = delete;

    Figure &operator=(const Figure &) = delete;

    Point<T> getCenter() const {
        return center;
    }

    friend std::ostream &operator<<(std::ostream &os, const Figure<T> &figure) {
        figure.print(os);
        return os;
    }

    friend std::istream &operator>>(std::istream &is, Figure<T> &figure) {
        T x, y;
        std::cout << "Enter center coordinates (x y):";
        is >> x >> y;
        figure.center = Point<T>(x, y);
        figure.input(is);
        return is;
    }

    virtual void print(std::ostream &os) const {
        os << "Figure with center (" << center.getX() << ", " << center.getY() << ")" << std::endl;
    }

    virtual double area() const = 0;

    virtual std::unique_ptr<Figure<T>> clone() const = 0;

    virtual void input(std::istream &is) = 0;

    operator double() const {
        return area();
    }

    bool operator==(const Figure &other) const {
        return area() == other.area();
    }

    bool operator>(const Figure &other) const {
        return area() > other.area();
    }

    bool operator<(const Figure &other) const {
        return area() < other.area();
    }
};

#endif