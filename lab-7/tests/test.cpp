#include "Game.h"
#include "Factory.h"
#include "NPC.h"
#include "Knight.h"
#include "Squirrel.h"
#include "Pegasus.h"
#include "ConsoleObserver.h"
#include "FileObserver.h"

#include <gtest/gtest.h>
#include <thread>
#include <chrono>
#include <memory>
#include <algorithm>

TEST(Factory_Tests, CreateNPC) {
    auto knight = Factory::createNPC("Knight", "Arthur", 50, 50);
    ASSERT_TRUE(knight != nullptr);
    EXPECT_EQ(knight->getType(), "Knight");
    EXPECT_EQ(knight->getName(), "Arthur");
    EXPECT_DOUBLE_EQ(knight->getX(), 50);
    EXPECT_DOUBLE_EQ(knight->getY(), 50);

    auto squirrel = Factory::createNPC("Squirrel", "Chip", 10, 10);
    ASSERT_TRUE(squirrel != nullptr);
    EXPECT_EQ(squirrel->getType(), "Squirrel");

    auto pegasus = Factory::createNPC("Pegasus", "Wind", 99, 99);
    ASSERT_TRUE(pegasus != nullptr);
    EXPECT_EQ(pegasus->getType(), "Pegasus");

    auto invalid = Factory::createNPC("Dragon", "Smaug", 0, 0);
    EXPECT_EQ(invalid, nullptr);
}

TEST(NPC_Tests, InRange) {
    auto knight = Factory::createNPC("Knight", "Lancelot", 0, 0);
    auto squirrel = Factory::createNPC("Squirrel", "Chip", 3, 4);
    EXPECT_TRUE(knight->isInRange(squirrel, 5));
    EXPECT_FALSE(knight->isInRange(squirrel, 4.9));
}

TEST(Game_Tests, InitialState) {
    Game game;
    const auto& npcs = game.getNPCs();
    EXPECT_EQ(npcs.size(), 50);

    for (auto& npc : npcs) {
        EXPECT_TRUE(npc->isAlive());
        EXPECT_GE(npc->getX(), 0);
        EXPECT_GE(npc->getY(), 0);
        EXPECT_LT(npc->getX(), 100);
        EXPECT_LT(npc->getY(), 100);
    }
}

TEST(Game_Tests, RunGame) {
    {
        Game game;
        std::thread t([&game]() {
            game.run();
        });
        t.join();
        EXPECT_TRUE(game.isStopped());
    }
}

TEST(Game_Tests, BattleCheck) {
    class TestGame : public Game {
    public:
        void externalStop() { stopGame(); }
    };

    TestGame game;
    const auto& npcsBefore = game.getNPCs();
    size_t countAliveBefore = std::count_if(npcsBefore.begin(), npcsBefore.end(),
        [](const std::shared_ptr<NPC>& npc){ return npc->isAlive(); });

    std::thread t([&game]() {
        game.run();
    });

    std::this_thread::sleep_for(std::chrono::seconds(15));
    game.externalStop();
    t.join();

    const auto& npcsAfter = game.getNPCs();
    size_t countAliveAfter = std::count_if(npcsAfter.begin(), npcsAfter.end(),
        [](const std::shared_ptr<NPC>& npc){ return npc->isAlive(); });

    EXPECT_LE(countAliveAfter, countAliveBefore);

    for (auto& npc : npcsAfter) {
        if (npc->isAlive()) {
            EXPECT_GE(npc->getX(), 0);
            EXPECT_GE(npc->getY(), 0);
            EXPECT_LT(npc->getX(), 100);
            EXPECT_LT(npc->getY(), 100);
        }
    }
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
