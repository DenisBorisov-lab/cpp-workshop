#include "Squirrel.h"
#include "Knight.h"
#include "Pegasus.h"

Squirrel::Squirrel(const std::string& name, double x, double y)
    : NPC(name, x, y) {}

void Squirrel::interact(NPC& other) {
    if (!other.isAlive()) {
        return;
    }
    other.interactWith(*this);
}

void Squirrel::interactWith(Knight& knight) {
    // Белки не взаимодействуют с Рыцарями
}

void Squirrel::interactWith(Squirrel& squirrel) {
    // Белки не сражаются друг с другом
}

void Squirrel::interactWith(Pegasus& pegasus) {
    if (!pegasus.isAlive()) {
        return;
    }
    // Белка убивает Пегаса
    std::string message = getType() + " " + getName() + " убила " + pegasus.getType() + " " + pegasus.getName();
    notifyObservers(message);
    pegasus.die();
}

std::string Squirrel::getType() const {
    return "Squirrel";
}
