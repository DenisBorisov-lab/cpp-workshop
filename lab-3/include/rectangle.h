#pragma once

#include "figure.h"

class Rectangle final : public Figure {
private:
    double width;
    double height;

public:
    Rectangle(double x = 0, double y = 0, double w = 0, double h = 0);

    std::pair<double, double> getCenter() const override;

    std::vector<std::pair<double, double>> getVertices() const override;

    double getArea() const override;

    Figure *clone() const override;

    bool operator==(const Figure &other) const override;

    friend std::ostream &operator<<(std::ostream &os, const Rectangle &rect);

    friend std::istream &operator>>(std::istream &is, Rectangle &rect);
};