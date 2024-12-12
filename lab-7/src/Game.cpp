#include "Game.h"
#include "Factory.h"
#include "ConsoleObserver.h"
#include "FileObserver.h"
#include "Knight.h"
#include "Squirrel.h"
#include "Pegasus.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <random>
#include <chrono>

Game::Game() {
    auto consoleObserver = std::make_shared<ConsoleObserver>();
    auto fileObserver = std::make_shared<FileObserver>("log.txt");
    observers_.push_back(consoleObserver);
    observers_.push_back(fileObserver);
    initNPCs();
}

void Game::initNPCs() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distType(0,2); 
    std::uniform_int_distribution<> distX(0, MAP_WIDTH-1);
    std::uniform_int_distribution<> distY(0, MAP_HEIGHT-1);

    std::vector<std::string> types = {"Squirrel", "Knight", "Pegasus"};

    for (int i = 0; i < 50; ++i) {
        std::string t = types[distType(gen)];
        double x = distX(gen);
        double y = distY(gen);
        auto npc = Factory::createNPC(t, "NPC" + std::to_string(i), x, y);
        if (npc) {
            for (auto& obs : observers_) {
                npc->attachObserver(obs);
            }
            npcs_.push_back(npc);
        }
    }
}

void Game::run() {
    movementThread_ = std::thread([this]{movementThreadFunc();});
    fightThread_ = std::thread([this]{fightThreadFunc();});

    auto start = std::chrono::steady_clock::now();
    while (!stop_.load()) {
        printMap();
        std::this_thread::sleep_for(std::chrono::seconds(1));
        auto now = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::seconds>(now - start).count() >= GAME_DURATION) {
            stopGame();
        }
    }

    if (movementThread_.joinable()) movementThread_.join();
    if (fightThread_.joinable()) fightThread_.join();

    {
        std::shared_lock lock(npcs_mutex_);
        std::lock_guard<std::mutex> cg(cout_mutex_);
        std::cout << "Game Over. Survivors:" << std::endl;
        for (auto &npc : npcs_) {
            if (npc->isAlive()) {
                std::cout << npc->getType() << " " << npc->getName() << std::endl;
            }
        }
    }
}

void Game::stopGame() {
    stop_.store(true);
    fightCV_.notify_all();
}

void Game::printMap() {
    std::shared_lock lock(npcs_mutex_);
    std::lock_guard<std::mutex> cg(cout_mutex_);
    std::cout << "Map State:" << std::endl;
    int aliveCount = 0;
    for (auto &npc : npcs_) {
        if (npc->isAlive()) {
            aliveCount++;
            std::cout << npc->getType() << " (" << npc->getName() << ") at (" << npc->getX() << "," << npc->getY() << ")\n";
        }
    }
    std::cout << "Total alive: " << aliveCount << std::endl;
}

void Game::movementThreadFunc() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distMove(-1,1);

    while (!stop_.load()) {
        {
            std::unique_lock wlock(npcs_mutex_);
            for (auto &npc : npcs_) {
                if (!npc->isAlive()) continue;

                int moveDist = 0;
                std::string type = npc->getType();
                if (type == "Squirrel") { moveDist = 5; }
                else if (type == "Knight") { moveDist = 30; }
                else if (type == "Pegasus") { moveDist = 30; }

                double newX = npc->getX() + distMove(gen)*moveDist;
                double newY = npc->getY() + distMove(gen)*moveDist;
                if (newX < 0) newX = 0;
                if (newX >= MAP_WIDTH) newX = MAP_WIDTH -1;
                if (newY < 0) newY = 0;
                if (newY >= MAP_HEIGHT) newY = MAP_HEIGHT -1;
                npc->setPosition(newX, newY);
            }

            // Проверка боёв
            for (size_t i = 0; i < npcs_.size(); ++i) {
                if (!npcs_[i]->isAlive()) continue;
                std::string atype = npcs_[i]->getType();

                for (size_t j = i+1; j < npcs_.size(); ++j) {
                    if (!npcs_[j]->isAlive()) continue;
                    std::string btype = npcs_[j]->getType();

                    double dx = npcs_[i]->getX() - npcs_[j]->getX();
                    double dy = npcs_[i]->getY() - npcs_[j]->getY();
                    double dist = std::sqrt(dx*dx + dy*dy);

                    bool canFight = false;
                    // Рыцарь убивает Белку
                    if (atype == "Knight" && btype == "Squirrel" && dist <= 10) {
                        canFight = true;
                    } 
                    // Белка убивает Пегаса
                    else if (atype == "Squirrel" && btype == "Pegasus" && dist <= 5) {
                        canFight = true;
                    }

                    if (canFight) {
                        FightTask task{npcs_[i], npcs_[j]};
                        {
                            std::lock_guard<std::mutex> ql(fightQueueMutex_);
                            fightQueue_.push(task);
                        }
                        fightCV_.notify_one();
                    }
                }
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void Game::fightThreadFunc() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dice(1,6);

    while (!stop_.load()) {
        FightTask task;
        {
            std::unique_lock ul(fightQueueMutex_);
            fightCV_.wait_for(ul, std::chrono::milliseconds(100), [this] { return !fightQueue_.empty() || stop_.load(); });
            if (stop_.load()) return;
            if (fightQueue_.empty()) continue;
            task = fightQueue_.front();
            fightQueue_.pop();
        }

        {
            std::shared_lock rlock(npcs_mutex_);
            if (!task.attacker->isAlive() || !task.defender->isAlive()) {
                continue;
            }
        }

        int attackVal = dice(gen);
        int defenseVal = dice(gen);

        if (attackVal > defenseVal) {
            std::unique_lock wlock(npcs_mutex_);
            if (task.attacker->isAlive() && task.defender->isAlive()) {
                std::string msg = task.attacker->getType() + " " + task.attacker->getName() + " убил " +
                                  task.defender->getType() + " " + task.defender->getName();
                task.defender->die();
                {
                    std::lock_guard<std::mutex> cg(cout_mutex_);
                    std::cout << msg << std::endl;
                }
                task.defender->notifyObservers(msg);
            }
        } 
        // иначе защита удачна, никто не умирает
    }
}
