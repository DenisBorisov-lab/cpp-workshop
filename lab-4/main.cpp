#include <iostream>
#include "point.hpp"
#include "figure.hpp"
#include "square.hpp"
#include "trapezoid.hpp"
#include "rectangle.hpp"
#include "figureArray.hpp"


void printDivider() {
    std::cout << "\n----------------------------------------\n";
}

int main() {
    auto square = std::make_shared<Square<int>>(Point<int>(0, 0), 1);
    std::cin >> *square;
    std::cout << *square << std::endl;

    printDivider();

    Array<std::shared_ptr<Figure<int>>> figures;

    figures.add(std::make_shared<Rectangle<int>>(Point<int>(0, 0), 4, 3));
    figures.add(std::make_shared<Square<int>>(Point<int>(1, 1), 5));
    figures.add(std::make_shared<Trapezoid<int>>(Point<int>(2, 2), 3, 6, 4));

    std::cout << "All figures:\n";
    figures.printAll();

    figures.remove(0);

    printDivider();
    std::cout << "All figures after removing" << std::endl;
    figures.printAll();


    printDivider();
    std::cout << "Total area: " << figures.getTotalArea() << std::endl;

    return 0;
}
