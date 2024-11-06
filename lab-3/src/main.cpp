#include <iostream>
#include <iomanip>
#include "figureArray.h"
#include "triangle.h"
#include "square.h"
#include "rectangle.h"

void printDivider() {
    std::cout << "\n----------------------------------------\n";
}

int main() {
    std::cout << std::fixed << std::setprecision(2);

    FigureArray array;

    std::cout << "\n1. Добавление фигур:";
    printDivider();

    array.add(new Triangle(0, 0, 6));
    array.add(new Square(2, 2, 4));
    array.add(new Rectangle(1, 1, 3, 5));

    std::cout << "\n2. Вывод всех фигур:";
    printDivider();
    array.printAll();

    std::cout << "\n3. Общая площадь:";
    printDivider();
    std::cout << "Общая площадь: " << array.getTotalArea() << "\n";

    std::cout << "\n4. Удаление фигуры:";
    printDivider();
    std::cout << "Удаление фигуры с индексом 1\n";
    array.remove(1);

    std::cout << "\n5. Обновленный массив:";
    printDivider();
    array.printAll();

    std::cout << "\n6. Доступ к по индексу 0:";
    printDivider();
    Figure *fig = array.at(0);
    std::cout << "Первая фигура:\n" << *fig << "\n";

    return 0;
}
