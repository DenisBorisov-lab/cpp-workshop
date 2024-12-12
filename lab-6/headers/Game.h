#ifndef GAME_H
#define GAME_H

#include "NPC.h"
#include "Observer.h"
#include <vector>
#include <memory>
#include <string>

class Game {
public:
    Game();
    void run();

private:
    void addNPC();
    void saveNPCs();
    void loadNPCs();
    void printNPCs();
    void battleMode();
    bool isNameTaken(const std::string& name) const;

    std::vector<std::shared_ptr<NPC>> npcs_;
    std::vector<std::shared_ptr<Observer>> observers_;
};

#endif // GAME_H
