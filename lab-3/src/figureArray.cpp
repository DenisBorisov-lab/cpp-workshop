#include "figureArray.h"
#include <iostream>

FigureArray::FigureArray(size_t initial_capacity)
        : size(0), capacity(initial_capacity) {
    figures = new Figure *[capacity];
}

FigureArray::~FigureArray() {
    for (size_t i = 0; i < size; ++i) {
        delete figures[i];
    }
    delete[] figures;
}

void FigureArray::add(Figure *fig) {
    if (size == capacity) {
        capacity *= 2;
        auto new_figures = new Figure *[capacity];
        for (size_t i = 0; i < size; ++i) {
            new_figures[i] = figures[i];
        }
        delete[] figures;
        figures = new_figures;
    }
    figures[size++] = fig->clone();
    delete fig;
}

void FigureArray::remove(size_t index) {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    delete figures[index];
    for (size_t i = index; i < size - 1; ++i) {
        figures[i] = figures[i + 1];
    }
    --size;
}

double FigureArray::getTotalArea() const {
    double total = 0;
    for (size_t i = 0; i < size; ++i) {
        total += figures[i]->getArea();
    }
    return total;
}

void FigureArray::printAll() const {
    for (size_t i = 0; i < size; ++i) {
        std::cout << "Figure " << i << ":\n" << *figures[i] << "\n\n";
    }
}

Figure *FigureArray::at(size_t index) const {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return figures[index];
}