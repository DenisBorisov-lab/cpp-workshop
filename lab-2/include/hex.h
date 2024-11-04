#ifndef HEX_H
#define HEX_H

#include <string>
#include <initializer_list>
#include <stdexcept>

class Hex {
private:
    unsigned char *digits;
    size_t size;

public:
    /**
     * Конструктор по умолчанию
     */
    Hex();

    /**
     * Конструктор с параметрами
     * @param n размер
     * @param t цифра числа
     */
    explicit Hex(const size_t &n, unsigned char t = 0);

    /**
     * Конструктор с последовательностью char
     * @param t последовательность
     */
    Hex(const std::initializer_list<unsigned char> &t);

    /**
     * Конструктор со строкой
     * @param t строка
     */
    explicit Hex(const std::string &t);


    /**
     * Копирование
     * @param other объект копирования
     */
    Hex(const Hex &other);

    /**
     * Конструктор перемещения
     * @param other объект перемещения
     */
    Hex(Hex &&other) noexcept;

    /**
     * Деструктор
     */
    virtual ~Hex() noexcept;

    /**
     * Стандартные геттеры
     */
    size_t getSize() const;

    unsigned char getDigit(size_t index) const;

    /**
     * Операция сложения
     * @param other слагаемое
     * @return сумма
     */
    Hex add(const Hex &other) const;

    /**
     * Операция вычитания
     * @param other вычитаемое
     * @return разность
     */
    Hex subtract(const Hex &other) const;

    bool isGreaterThan(const Hex &other) const;

    bool isLessThan(const Hex &other) const;

    bool isEqual(const Hex &other) const;

    /**
     * Преобразование в строку
     *
     * @return строка объекта
     */
    std::string toString() const;
};

#endif
