#pragma once
#include <exception>

class NegativeSideException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Error: Side length cannot be negative!";
    }
};