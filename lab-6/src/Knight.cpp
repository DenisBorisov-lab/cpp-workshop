#include "Knight.h"
#include "Squirrel.h"
#include "Pegasus.h"

Knight::Knight(const std::string& name, double x, double y)
    : NPC(name, x, y) {}

void Knight::interact(NPC& other) {
    if (!other.isAlive()) {
        return;
    }
    other.interactWith(*this);
}

void Knight::interactWith(Knight& knight) {
    // Рыцари не сражаются друг с другом
}

void Knight::interactWith(Squirrel& squirrel) {
    if (!squirrel.isAlive()) {
        return;
    }
    // Рыцарь убивает Белку
    std::string message = getType() + " " + getName() + " убил " + squirrel.getType() + " " + squirrel.getName();
    notifyObservers(message);
    squirrel.die();
}

void Knight::interactWith(Pegasus& pegasus) {
    // Рыцари не взаимодействуют с Пегасами
}

std::string Knight::getType() const {
    return "Knight";
}
