#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "figure.hpp"

template<Scalar T>
class Rectangle : public Figure<T> {
private:
    T width;
    T height;

public:
    Rectangle(const Point<T> &center, T w, T h)
            : Figure<T>(center) {
        if (w <= 0 || h <= 0) {
            throw std::invalid_argument("Width and height must be positive");
        }
        width = w;
        height = h;
    }

    double area() const override {
        return width * height;
    }

    void print(std::ostream &os) const override {
        Figure<T>::print(os);
        os << "Width: " << width << ", height: " << height;
    }

    std::unique_ptr<Figure<T>> clone() const override {
        return std::make_unique<Rectangle<T>>(this->center, width, height);
    }

private:
    void input(std::istream &is) override {
        std::cout << "Enter width and height:";
        is >> width >> height;
    }
};

#endif