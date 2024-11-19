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
        if (w < 0 || h < 0) {
            throw std::invalid_argument("Width and height must be positive");
        }
        width = w;
        height = h;
    }

    double area() const override {
        return width * height;
    }

    std::vector<std::unique_ptr<Point<T>>> getVertices() const override {
        std::vector<std::unique_ptr<Point<T>>> vertices;

        T halfWidth = width / 2;
        T halfHeight = height / 2;

        vertices.push_back(std::make_unique<Point<T>>(
                this->center.getX() - halfWidth,
                this->center.getY() - halfHeight));

        vertices.push_back(std::make_unique<Point<T>>(
                this->center.getX() + halfWidth,
                this->center.getY() - halfHeight));

        vertices.push_back(std::make_unique<Point<T>>(
                this->center.getX() + halfWidth,
                this->center.getY() + halfHeight));

        vertices.push_back(std::make_unique<Point<T>>(
                this->center.getX() - halfWidth,
                this->center.getY() + halfHeight));

        return vertices;
    }

    void print(std::ostream &os) const override {
        Figure<T>::print(os);
        os << "Width: " << width << ", height: " << height << std::endl;
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
        return std::make_unique<Rectangle<T>>(this->center, width, height);
    }

private:
    void input(std::istream &is) override {
        std::cout << "Enter width and height:";
        is >> width >> height;
    }
};

#endif