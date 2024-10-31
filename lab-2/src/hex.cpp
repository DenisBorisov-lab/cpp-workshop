#include "hex.h"

Hex::Hex() : digits(nullptr), size(0) {}

Hex::Hex(const size_t &n, unsigned char t) : size(n) {
    if (t > 15) throw std::invalid_argument("Invalid hex digit");
    digits = new unsigned char[n];
    for (size_t i = 0; i < n; ++i) {
        digits[i] = t;
    }
}

Hex::Hex(const std::initializer_list<unsigned char> &t) : size(t.size()) {
    digits = new unsigned char[size];
    size_t i = 0;
    for (auto digit: t) {
        if (digit > 15) throw std::invalid_argument("Invalid hex digit");
        digits[i++] = digit;
    }
}

Hex::Hex(const std::string &t) {
    size = t.length();
    digits = new unsigned char[size];

    for (size_t i = 0; i < size; ++i) {
        char c = t[size - 1 - i];
        if ((c >= '0' && c <= '9')) {
            digits[i] = c - '0';
        } else if ((c >= 'A' && c <= 'F')) {
            digits[i] = c - 'A' + 10;
        } else if ((c >= 'a' && c <= 'f')) {
            digits[i] = c - 'a' + 10;
        } else {
            delete[] digits;
            throw std::invalid_argument("Invalid hex string");
        }
    }
}

Hex::Hex(const Hex &other) : size(other.size) {
    digits = new unsigned char[size];
    for (size_t i = 0; i < size; ++i) {
        digits[i] = other.digits[i];
    }
}

Hex::Hex(Hex &&other) noexcept: digits(other.digits), size(other.size) {
    other.digits = nullptr;
    other.size = 0;
}

Hex::~Hex() noexcept {
    delete[] digits;
}

void Hex::validateHexDigit(unsigned char digit) const {
    if (digit > 15) throw std::invalid_argument("Invalid hex digit");
}

size_t Hex::getSize() const {
    return size;
}

unsigned char Hex::getDigit(size_t index) const {
    if (index >= size) throw std::out_of_range("Index out of range");
    return digits[index];
}

Hex Hex::add(const Hex &other) const {
    size_t maxSize = std::max(size, other.size);
    Hex result(maxSize + 1, 0);

    unsigned char carry = 0;
    for (size_t i = 0; i < maxSize; ++i) {
        unsigned char sum = carry;
        if (i < size) sum += digits[i];
        if (i < other.size) sum += other.digits[i];

        result.digits[i] = sum % 16;
        carry = sum / 16;
    }
    if (carry) result.digits[maxSize] = carry;

    return result;
}

Hex &Hex::operator=(const Hex &other) {
    if (this != &other) {  // проверка на самоприсваивание
        delete[] digits;    // освобождаем старую память
        size = other.size;
        digits = new unsigned char[size];
        for (size_t i = 0; i < size; ++i) {
            digits[i] = other.digits[i];
        }
    }
    return *this;
}

Hex Hex::subtract(const Hex &other) const {
    if (isLessThan(other)) throw std::invalid_argument("Cannot subtract larger number");

    Hex result(size, 0);
    int borrow = 0;

    for (size_t i = 0; i < size; ++i) {
        int diff = digits[i] - borrow;
        if (i < other.size) diff -= other.digits[i];

        if (diff < 0) {
            diff += 16;
            borrow = 1;
        } else {
            borrow = 0;
        }

        result.digits[i] = diff;
    }

    return result;
}

void Hex::addAssign(const Hex &other) {
    Hex result = add(other);
    *this = result;
}

void Hex::subtractAssign(const Hex &other) {
    Hex result = subtract(other);
    *this = result;
}

bool Hex::isGreaterThan(const Hex &other) const {
    if (size != other.size) return size > other.size;

    for (size_t i = size - 1; i < size; --i) {
        if (digits[i] != other.digits[i]) {
            return digits[i] > other.digits[i];
        }
    }
    return false;
}

bool Hex::isLessThan(const Hex &other) const {
    return !isGreaterThan(other) && !isEqual(other);
}

bool Hex::isEqual(const Hex &other) const {
    if (size != other.size) return false;

    for (size_t i = 0; i < size; ++i) {
        if (digits[i] != other.digits[i]) return false;
    }
    return true;
}

std::string Hex::toString() const {
    if (size == 0) return "0";

    // Находим первую значащую цифру (пропускаем ведущие нули)
    size_t firstNonZero = size;
    for (size_t i = size; i > 0; --i) {
        if (digits[i - 1] != 0) {
            firstNonZero = i - 1;
            break;
        }
    }

    // Если все цифры нули, возвращаем "0"
    if (firstNonZero == size) return "0";

    std::string result;
    // Проходим от старшего разряда к младшему
    for (size_t i = firstNonZero + 1; i > 0; --i) {
        char digit = digits[i - 1];
        result += (digit < 10) ? ('0' + digit) : ('A' + digit - 10);
    }
    return result;
}
