#include "Game.h"
#include "Factory.h"
#include "ConsoleObserver.h"
#include "FileObserver.h"

#include <iostream>
#include <fstream>
#include <algorithm>

Game::Game() {
    auto consoleObserver = std::make_shared<ConsoleObserver>();
    auto fileObserver = std::make_shared<FileObserver>("log.txt");
    observers_.push_back(consoleObserver);
    observers_.push_back(fileObserver);
}

void Game::run() {
    int choice = -1;
    while (choice != 0) {
        std::cout << "\n--- Бальдурс Гейт 4 ---\n";
        std::cout << "1. Add NPC\n";
        std::cout << "2. Save NPCs to file\n";
        std::cout << "3. Load NPCs from file\n";
        std::cout << "4. Print NPCs\n";
        std::cout << "5. Battle Mode\n";
        std::cout << "0. Exit\n";
        std::cout << "Choose an option: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                addNPC();
                break;
            case 2:
                saveNPCs();
                break;
            case 3:
                loadNPCs();
                break;
            case 4:
                printNPCs();
                break;
            case 5:
                battleMode();
                break;
            case 0:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid option!\n";
        }
    }
}

void Game::addNPC() {
    std::string type, name;
    double x, y;

    std::cout << "Enter NPC type (Knight/Squirrel/Pegasus): ";
    std::cin >> type;
    std::cout << "Enter NPC name: ";
    std::cin >> name;
    if (isNameTaken(name)) {
        std::cout << "Name already taken!\n";
        return;
    }
    std::cout << "Enter X coordinate (0-500): ";
    std::cin >> x;
    std::cout << "Enter Y coordinate (0-500): ";
    std::cin >> y;

    if (x < 0 || x > 500 || y < 0 || y > 500) {
        std::cout << "Coordinates out of bounds!\n";
        return;
    }

    auto npc = Factory::createNPC(type, name, x, y);
    if (npc) {
        for (const auto& observer : observers_) {
            npc->attachObserver(observer);
        }
        npcs_.push_back(npc);
        std::cout << "NPC added successfully.\n";
    } else {
        std::cout << "Invalid NPC type!\n";
    }
}

bool Game::isNameTaken(const std::string& name) const {
    for (const auto& npc : npcs_) {
        if (npc->getName() == name && npc->isAlive()) {
            return true;
        }
    }
    return false;
}

void Game::saveNPCs() {
    std::ofstream file("npcs.txt");
    if (file.is_open()) {
        for (const auto& npc : npcs_) {
            if (npc->isAlive()) {
                file << npc->getType() << " " << npc->getName() << " " << npc->getX() << " " << npc->getY() << "\n";
            }
        }
        file.close();
        std::cout << "NPCs saved to npcs.txt.\n";
    } else {
        std::cout << "Failed to open file for writing.\n";
    }
}

void Game::loadNPCs() {
    std::ifstream file("npcs.txt");
    if (file.is_open()) {
        npcs_.clear();
        std::string type, name;
        double x, y;
        while (file >> type >> name >> x >> y) {
            if (x < 0 || x > 500 || y < 0 || y > 500) {
                std::cout << "Invalid coordinates in file for NPC " << name << ". Skipping.\n";
                continue;
            }
            if (isNameTaken(name)) {
                std::cout << "Duplicate name in file for NPC " << name << ". Skipping.\n";
                continue;
            }
            auto npc = Factory::createNPC(type, name, x, y);
            if (npc) {
                for (const auto& observer : observers_) {
                    npc->attachObserver(observer);
                }
                npcs_.push_back(npc);
            } else {
                std::cout << "Invalid NPC type in file: " << type << ". Skipping.\n";
            }
        }
        file.close();
        std::cout << "NPCs loaded from npcs.txt.\n";
    } else {
        std::cout << "Failed to open file for reading.\n";
    }
}

void Game::printNPCs() {
    if (npcs_.empty()) {
        std::cout << "No NPCs to display.\n";
        return;
    }
    std::cout << "\n--- List of NPCs ---\n";
    for (const auto& npc : npcs_) {
        if (npc->isAlive()) {
            std::cout << npc->getType() << " " << npc->getName() << " at (" << npc->getX() << ", " << npc->getY() << ")\n";
        }
    }
}

void Game::battleMode() {
    if (npcs_.size() < 2) {
        std::cout << "Недостаточно NPC для боя.\n";
        return;
    }
    double range;
    std::cout << "Введите дальность боя: ";
    std::cin >> range;

    bool someoneDied;
    do {
        someoneDied = false;
        for (size_t i = 0; i < npcs_.size(); ++i) {
            auto npc1 = npcs_[i];
            if (!npc1->isAlive()) continue;
            for (size_t j = i + 1; j < npcs_.size(); ++j) {
                auto npc2 = npcs_[j];
                if (!npc2->isAlive()) continue;
                if (npc1->isInRange(npc2, range)) {
                    // Жертва принимает взаимодействие от атакующего
                    npc2->acceptInteraction(npc1);
                }
            }
        }
        // Проверяем, погиб ли кто-нибудь
        for (const auto& npc : npcs_) {
            if (!npc->isAlive()) {
                someoneDied = true;
                break;
            }
        }
        // Удаляем погибших NPC
        npcs_.erase(std::remove_if(npcs_.begin(), npcs_.end(),
            [](const std::shared_ptr<NPC>& npc) { return !npc->isAlive(); }), npcs_.end());
    } while (someoneDied);
}

