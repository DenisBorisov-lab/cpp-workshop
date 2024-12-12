#include "Pegasus.h"
#include "Knight.h"
#include "Squirrel.h"

Pegasus::Pegasus(const std::string& name, double x, double y)
    : NPC(name, x, y) {}

void Pegasus::interact(NPC& other) {
    if (!other.isAlive()) {
        return;
    }
    other.interactWith(*this);
}

void Pegasus::interactWith(Knight& knight) {
    // Пегасы не взаимодействуют с Рыцарями
}

void Pegasus::interactWith(Squirrel& squirrel) {
    // Пегасы не взаимодействуют с Белками
}

void Pegasus::interactWith(Pegasus& pegasus) {
    // Пегасы не сражаются друг с другом
}

std::string Pegasus::getType() const {
    return "Pegasus";
}
