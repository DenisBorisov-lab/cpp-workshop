#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <memory>
#include <iostream>
#include <concepts>
#include <cassert>

template<typename T>
concept FigureType = requires(T t) {
    { t->area() } -> std::convertible_to<double>;
    { t->print(std::cout) };
};

template<FigureType T>
class Array {
private:
    size_t _size;
    size_t _capacity;
    std::shared_ptr<T[]> _array;

    void resize(size_t new_capacity) {
        auto new_array = std::shared_ptr<T[]>(new T[new_capacity]);

        for (size_t i = 0; i < _size; ++i) {
            new_array[i] = std::move(_array[i]);
        }

        _array = std::move(new_array);
        _capacity = new_capacity;
    }

public:
    Array() : _size(0), _capacity(1), _array(new T[1]) {}

    // Добавление элемента
    void add(const T& item) {
        if (_size == _capacity) {
            resize(_capacity * 2);
        }
        _array[_size++] = item;
    }

    void remove(size_t index) {
        assert(index < _size && "Index out of range");

        for (size_t i = index; i < _size - 1; ++i) {
            _array[i] = std::move(_array[i + 1]);
        }
        --_size;
    }

    T& operator[](size_t index) {
        assert(index < _size && "Index out of range");
        return _array[index];
    }

    const T& operator[](size_t index) const {
        assert(index < _size && "Index out of range");
        return _array[index];
    }

    size_t size() const {
        return _size;
    }

    double getTotalArea() const {
        double total = 0;
        for (size_t i = 0; i < _size; ++i) {
            total += double(*_array[i]);  // разыменовываем указатель
        }
        return total;
    }

    void printAll(std::ostream& os = std::cout) const {
        for (size_t i = 0; i < _size; ++i) {
            _array[i]->print(os);
            os << "\nArea: " << _array[i]->area() << "\n";
        }
    }
};

#endif
