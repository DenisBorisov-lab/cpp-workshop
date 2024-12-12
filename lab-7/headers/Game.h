#ifndef GAME_H
#define GAME_H

#include "NPC.h"
#include "Observer.h"
#include <vector>
#include <memory>
#include <string>
#include <queue>
#include <mutex>
#include <shared_mutex>
#include <condition_variable>
#include <atomic>
#include <thread>

constexpr int MAP_WIDTH = 100;
constexpr int MAP_HEIGHT = 100;
constexpr int GAME_DURATION = 30; // секунд

struct FightTask {
    std::shared_ptr<NPC> attacker;
    std::shared_ptr<NPC> defender;
};

class Game {
public:
    Game();
    void run();
    void stopGame();

    const std::vector<std::shared_ptr<NPC>>& getNPCs() const { return npcs_; }
    bool isStopped() const { return stop_.load(); }

private:
    void initNPCs();
    void printMap();

    void movementThreadFunc();
    void fightThreadFunc();

    std::vector<std::shared_ptr<NPC>> npcs_;
    std::vector<std::shared_ptr<Observer>> observers_;

    std::shared_mutex npcs_mutex_;
    std::mutex cout_mutex_;

    std::queue<FightTask> fightQueue_;
    std::mutex fightQueueMutex_;
    std::condition_variable fightCV_;

    std::atomic<bool> stop_{false};

    std::thread movementThread_;
    std::thread fightThread_;
};

#endif // GAME_H
