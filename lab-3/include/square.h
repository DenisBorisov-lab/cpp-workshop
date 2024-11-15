#pragma once

#include "figure.h"

class Square final : public Figure {
private:
    double side;

public:
    Square(double x = 0, double y = 0, double s = 0);

    std::pair<double, double> getCenter() const override;

    std::vector<std::pair<double, double>> getVertices() const override;

    double getArea() const override;

    Figure *clone() const override;

    bool operator==(const Figure &other) const override;

    friend std::ostream &operator<<(std::ostream &os, const Square &sq);

    friend std::istream &operator>>(std::istream &is, Square &sq);
};