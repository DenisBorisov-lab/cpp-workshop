#ifndef FACTORY_H
#define FACTORY_H

#include <memory>
#include <string>
#include "NPC.h"

class Factory {
public:
    static std::shared_ptr<NPC> createNPC(const std::string& type, const std::string& name, double x, double y);
};

#endif // FACTORY_H
