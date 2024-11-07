#pragma once

#include <vector>
#include "figure.h"

class Trapezoid : public Figure {
private:
    double topSide;
    double bottomSide;
    double height;

public:
    Trapezoid(double x = 0, double y = 0, double top = 0, double bottom = 0, double h = 0);

    double getHeight() const { return height; }

    double getTopSide() const { return topSide; }

    double getBottomSide() const { return bottomSide; }

    std::vector<std::pair<double, double>> getVertices() const override;

    std::pair<double, double> getCenter() const override;

    double getArea() const override;

    Figure *clone() const override;

    bool operator==(const Figure &other) const override;

    friend std::ostream &operator<<(std::ostream &os, const Trapezoid &tr);

    friend std::istream &operator>>(std::istream &is, Trapezoid &tr);
};