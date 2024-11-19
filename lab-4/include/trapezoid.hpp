#ifndef TRAPEZOID_HPP
#define TRAPEZOID_HPP

#include "figure.hpp"

template<Scalar T>
class Trapezoid : public Figure<T> {
private:
    T topBase;
    T bottomBase;
    T height;

public:
    Trapezoid(const Point<T> &center, T top, T bottom, T h)
            : Figure<T>(center) {
        if (top < 0 || bottom < 0 || h < 0) {
            throw std::invalid_argument("All trapezoid fields must be positive");
        }
        topBase = top;
        bottomBase = bottom;
        height = h;
    }

    double area() const override {
        return (topBase + bottomBase) * height / 2.0;
    }

    std::vector<std::unique_ptr<Point<T>>> getVertices() const override {
        std::vector<std::unique_ptr<Point<T>>> vertices;

        T halfTop = topBase / 2;
        T halfBottom = bottomBase / 2;
        T halfHeight = height / 2;

        vertices.push_back(std::make_unique<Point<T>>(
                this->center.getX() - halfTop,
                this->center.getY() - halfHeight));

        vertices.push_back(std::make_unique<Point<T>>(
                this->center.getX() + halfTop,
                this->center.getY() - halfHeight));

        vertices.push_back(std::make_unique<Point<T>>(
                this->center.getX() + halfBottom,
                this->center.getY() + halfHeight));

        vertices.push_back(std::make_unique<Point<T>>(
                this->center.getX() - halfBottom,
                this->center.getY() + halfHeight));

        return vertices;
    }

    void print(std::ostream &os) const override {
        Figure<T>::print(os);
        os << "Top base: " << topBase
           << ", bottom base: " << bottomBase
           << ", height:" << height << std::endl;

        auto vertices = getVertices();
        os << "Vertices:" << std::endl;
        for (size_t i = 0; i < vertices.size(); ++i) {
            os << "  " << (i + 1) << ": ("
               << vertices[i]->getX() << ", "
               << vertices[i]->getY() << ")"
               << std::endl;
        }
    }

    std::unique_ptr<Figure<T>> clone() const override {
        return std::make_unique<Trapezoid<T>>(this->center, topBase, bottomBase, height);
    }

private:
    void input(std::istream &is) override {
        std::cout << "Enter top base, bottom base and height:";
        is >> topBase >> bottomBase >> height;
    }
};

#endif