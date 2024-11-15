#ifndef SQUARE_HPP
#define SQUARE_HPP

#include "figure.hpp"

template<Scalar T>
class Square : public Figure<T> {
private:
    T side;

public:
    Square(const Point<T> &center, T side_length)
            : Figure<T>(center) {
        if (side_length <= 0) {
            throw std::invalid_argument("Side length must be positive");
        }
        side = side_length;
    }

    double area() const override {
        return side * side;
    }

    void print(std::ostream &os) const override {
        Figure<T>::print(os);
        os << "Side length: " << side;
    }

    std::unique_ptr<Figure<T>> clone() const override {
        return std::make_unique<Square<T>>(this->center, side);
    }

private:
    void input(std::istream &is) override {
        std::cout << "Enter side length:";
        is >> side;
    }
};

#endif