#include "Factory.h"
#include "Knight.h"
#include "Squirrel.h"
#include "Pegasus.h"

std::shared_ptr<NPC> Factory::createNPC(const std::string& type, const std::string& name, double x, double y) {
    if (type == "Knight") {
        return std::make_shared<Knight>(name, x, y);
    } else if (type == "Squirrel") {
        return std::make_shared<Squirrel>(name, x, y);
    } else if (type == "Pegasus") {
        return std::make_shared<Pegasus>(name, x, y);
    } else {
        return nullptr;
    }
}
