#ifndef HEX_H
#define HEX_H

#include <string>
#include <initializer_list>
#include <stdexcept>

class Hex {
private:
    unsigned char* digits;
    size_t size;

    void validateHexDigit(unsigned char digit) const;

public:
    // Конструкторы
    Hex();
    Hex(const size_t& n, unsigned char t = 0);
    Hex(const std::initializer_list<unsigned char>& t);
    Hex(const std::string& t);
    Hex(const Hex& other);
    Hex(Hex&& other) noexcept;

    // Оператор присваивания
    Hex& operator=(const Hex& other);

    // Деструктор
    virtual ~Hex() noexcept;

    // Методы доступа
    size_t getSize() const;
    unsigned char getDigit(size_t index) const;

    // Арифметические операции
    Hex add(const Hex& other) const;
    Hex subtract(const Hex& other) const;
    void addAssign(const Hex& other);
    void subtractAssign(const Hex& other);

    // Операции сравнения
    bool isGreaterThan(const Hex& other) const;
    bool isLessThan(const Hex& other) const;
    bool isEqual(const Hex& other) const;

    // Вспомогательные методы
    std::string toString() const;
};

#endif
