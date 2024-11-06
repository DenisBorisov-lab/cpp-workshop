#pragma once

#include "figure.h"

class FigureArray {
private:
    Figure **figures;  // массив указателей на фигуры
    size_t size;      // текущий размер
    size_t capacity;  // вместимость массива

public:
    FigureArray(size_t initial_capacity = 10);

    ~FigureArray();

    // Запрет копирования и присваивания
    FigureArray(const FigureArray &) = delete;

    FigureArray &operator=(const FigureArray &) = delete;

    void add(Figure *fig);

    void remove(size_t index);

    double getTotalArea() const;

    void printAll() const;

    // Дополнительные методы
    size_t getSize() const { return size; }

    bool empty() const { return size == 0; }

    Figure *at(size_t index) const;
};