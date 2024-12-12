#ifndef PEGASUS_H
#define PEGASUS_H

#include "NPC.h"

class Pegasus : public NPC {
public:
    Pegasus(const std::string& name, double x, double y);

    void interact(NPC& other) override;
    void interactWith(Knight& knight) override;
    void interactWith(Squirrel& squirrel) override;
    void interactWith(Pegasus& pegasus) override;

    std::string getType() const override;
};

#endif // PEGASUS_H
