#include "Squirrel.h"
#include "Knight.h"
#include "Pegasus.h"

Squirrel::Squirrel(const std::string& name, double x, double y)
    : NPC(name, x, y) {}

void Squirrel::interact(NPC& other) {
    if (!other.isAlive()) return;
    other.interactWith(*this);
}

void Squirrel::interactWith(Knight& knight) {
}

void Squirrel::interactWith(Squirrel& squirrel) {
}

void Squirrel::interactWith(Pegasus& pegasus) {
}

std::string Squirrel::getType() const {
    return "Squirrel";
}
