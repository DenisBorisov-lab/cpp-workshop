#ifndef SQUIRREL_H
#define SQUIRREL_H

#include "NPC.h"

class Squirrel : public NPC {
public:
    Squirrel(const std::string& name, double x, double y);

    void interact(NPC& other) override;
    void interactWith(Knight& knight) override;
    void interactWith(Squirrel& squirrel) override;
    void interactWith(Pegasus& pegasus) override;

    std::string getType() const override;
};

#endif // SQUIRREL_H
