#include <iostream>
#include <memory_resource>
#include "../include/CustomMemoryResource.h"
#include "../include/Stack.h"

struct ComplexType {
    int id;
    std::string name;
    double value;

    ComplexType(int i, const std::string &n, double v)
            : id(i), name(n), value(v) {}
};

int main() {
    CustomMemoryResource customResource(1024);
    std::pmr::polymorphic_allocator<int> allocator(&customResource);
    Stack<int, std::pmr::polymorphic_allocator<int>> intStack{10, allocator};

    intStack.push(1);
    intStack.push(2);
    intStack.push(3);

    intStack.pop();

    std::cout << "Содержимое стека с int:" << std::endl;
    for (const auto &item: intStack) {
        std::cout << item << std::endl;
    }


    CustomMemoryResource customResource2(2048);
    std::pmr::polymorphic_allocator<ComplexType> allocator2(&customResource2);
    Stack<ComplexType, std::pmr::polymorphic_allocator<ComplexType>> complexStack{10, allocator2};

    complexStack.push(ComplexType(1, "Item1", 10.5));
    complexStack.push(ComplexType(2, "Item2", 20.5));
    complexStack.push(ComplexType(3, "Item3", 30.5));

    std::cout << "\nСодержимое стека с ComplexType:" << std::endl;
    for (const auto &item: complexStack) {
        std::cout << "ID: " << item.id << ", Name: " << item.name << ", Value: " << item.value << std::endl;
    }

    return 0;
}
