#include <iostream>
#include "hex.h"

int main() {
    try {
        Hex a("A5");
        Hex b("3F");

        Hex sum = a.add(b);
        Hex diff = a.subtract(b);

        std::cout << "A5 + 3F = " << sum.toString() << std::endl;
        std::cout << "A5 - 3F = " << diff.toString() << std::endl;

        std::cout << "A5 > 3F: " << a.isGreaterThan(b) << std::endl;
        std::cout << "A5 = 3F: " << a.isEqual(b) << std::endl;
    }
    catch (const std::exception &e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    return 0;
}
