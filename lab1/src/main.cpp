#include <iostream>
#include <string>
#include "solution.h"

int main() {
    std::string day;
    int value;

    std::cout << "День недели:" << std::endl;
    std::cin >> day;
    std::cout << "Числовое значение:" << std::endl;
    std::cin >> value;

    std::cout << (isAfraid(day, value) ? "Я боюсь" : "Я не боюсь") << std::endl;
    return 0;
}
