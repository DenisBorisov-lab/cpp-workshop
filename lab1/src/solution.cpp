#include <stdexcept>
#include <unordered_map>
#include <functional>
#include "solution.h"

bool isAfraid(const std::string &day, int value) {
    static const std::unordered_map<std::string, std::function<bool(int)>> dayChecks = {
            {"Понедельник", [](int v) { return v == 12; }},
            {"Вторник",     [](int v) { return v > 95; }},
            {"Среда",       [](int v) { return v == 34; }},
            {"Четверг",     [](int v) { return v == 0; }},
            {"Пятница",     [](int v) { return v % 2 == 0; }},
            {"Суббота",     [](int v) { return v == 56; }},
            {"Воскресенье", [](int v) { return v == 666 || v == -666; }}
    };

    auto it = dayChecks.find(day);
    if (it != dayChecks.end()) {
        return it->second(value);
    }

    throw std::runtime_error("Invalid day of the week!");
}