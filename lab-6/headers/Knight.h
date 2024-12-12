#ifndef KNIGHT_H
#define KNIGHT_H

#include "NPC.h"

class Knight : public NPC {
public:
    Knight(const std::string& name, double x, double y);

    void interact(NPC& other) override;
    void interactWith(Knight& knight) override;
    void interactWith(Squirrel& squirrel) override;
    void interactWith(Pegasus& pegasus) override;

    std::string getType() const override;
};

#endif // KNIGHT_H
