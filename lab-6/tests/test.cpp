#include "NPC.h"
#include "Knight.h"
#include "Squirrel.h"
#include "Pegasus.h"
#include "Factory.h"
#include "ConsoleObserver.h"

#include <gtest/gtest.h>
#include <memory>
#include <vector>
#include <algorithm>

// Тесты создания NPC
TEST(NPC_Class_Tests, Creation) {
    auto knight = Factory::createNPC("Knight", "Arthur", 100, 100);
    ASSERT_TRUE(knight != nullptr);
    EXPECT_EQ(knight->getType(), "Knight");
    EXPECT_EQ(knight->getName(), "Arthur");
    EXPECT_EQ(knight->getX(), 100);
    EXPECT_EQ(knight->getY(), 100);
}

TEST(NPC_Class_Tests, InvalidCreation) {
    auto npc = Factory::createNPC("Dragon", "Smaug", 0, 0);
    ASSERT_TRUE(npc == nullptr);
}

TEST(NPC_Class_Tests, InRange) {
    auto knight = Factory::createNPC("Knight", "Lancelot", 0, 0);
    auto squirrel = Factory::createNPC("Squirrel", "Chip", 3, 4);
    EXPECT_TRUE(knight->isInRange(squirrel, 5));
    EXPECT_FALSE(knight->isInRange(squirrel, 4.9));
}

// Тесты взаимодействия
TEST(Battle_Tests, KnightKillsSquirrel) {
    auto knight = Factory::createNPC("Knight", "Lancelot", 0, 0);
    auto squirrel = Factory::createNPC("Squirrel", "Chip", 0, 0);
    auto observer = std::make_shared<ConsoleObserver>();
    knight->attachObserver(observer);
    squirrel->attachObserver(observer);

    // Белка принимает взаимодействие от Рыцаря
    squirrel->acceptInteraction(knight);
    EXPECT_FALSE(squirrel->isAlive());
    EXPECT_TRUE(knight->isAlive());
}

TEST(Battle_Tests, SquirrelKillsPegasus) {
    auto squirrel = Factory::createNPC("Squirrel", "Chip", 0, 0);
    auto pegasus = Factory::createNPC("Pegasus", "Wind", 0, 0);
    auto observer = std::make_shared<ConsoleObserver>();
    squirrel->attachObserver(observer);
    pegasus->attachObserver(observer);

    // Пегас принимает взаимодействие от Белки
    pegasus->acceptInteraction(squirrel);
    EXPECT_FALSE(pegasus->isAlive());
    EXPECT_TRUE(squirrel->isAlive());
}

TEST(Battle_Tests, PegasusDoesNotAttack) {
    auto pegasus = Factory::createNPC("Pegasus", "Wind", 0, 0);
    auto knight = Factory::createNPC("Knight", "Lancelot", 0, 0);
    auto observer = std::make_shared<ConsoleObserver>();
    pegasus->attachObserver(observer);
    knight->attachObserver(observer);

    // Рыцарь принимает взаимодействие от Пегаса
    knight->acceptInteraction(pegasus);
    EXPECT_TRUE(knight->isAlive());
    EXPECT_TRUE(pegasus->isAlive());
}

TEST(Battle_Tests, NPCsOutOfRange) {
    auto knight = Factory::createNPC("Knight", "Arthur", 0, 0);
    auto squirrel = Factory::createNPC("Squirrel", "Chip", 100, 100); // Расстояние больше 5
    EXPECT_FALSE(knight->isInRange(squirrel, 5));

    // Поскольку NPC находятся вне диапазона, они не взаимодействуют
    // Не вызываем acceptInteraction
    EXPECT_TRUE(knight->isAlive());
    EXPECT_TRUE(squirrel->isAlive());
}

TEST(Battle_Tests, DeadNPCDoesNotInteract) {
    auto knight = Factory::createNPC("Knight", "Arthur", 0, 0);
    auto squirrel = Factory::createNPC("Squirrel", "Chip", 0, 0);
    auto pegasus = Factory::createNPC("Pegasus", "Wind", 0, 0);
    auto observer = std::make_shared<ConsoleObserver>();
    knight->attachObserver(observer);
    squirrel->attachObserver(observer);
    pegasus->attachObserver(observer);

    // Рыцарь убивает Белку
    squirrel->acceptInteraction(knight);
    EXPECT_FALSE(squirrel->isAlive());

    // Мертвая Белка пытается взаимодействовать с Пегасом
    pegasus->acceptInteraction(squirrel);
    EXPECT_TRUE(pegasus->isAlive());
}

TEST(Battle_Tests, ObserverNotifications) {
    auto knight = Factory::createNPC("Knight", "Arthur", 0, 0);
    auto squirrel = Factory::createNPC("Squirrel", "Chip", 0, 0);

    // Создаем наблюдателя, который записывает сообщения в строку
    class StringObserver : public Observer {
    public:
        void update(const std::string& message) override {
            messages += message + "\n";
        }
        std::string messages;
    };

    auto stringObserver = std::make_shared<StringObserver>();
    knight->attachObserver(stringObserver);
    squirrel->attachObserver(stringObserver);

    // Белка принимает взаимодействие от Рыцаря
    squirrel->acceptInteraction(knight);

    EXPECT_FALSE(squirrel->isAlive());
    EXPECT_TRUE(knight->isAlive());

    std::string expectedMessage = "Knight Arthur убил Squirrel Chip\n";
    EXPECT_EQ(stringObserver->messages, expectedMessage);
}

TEST(Battle_Tests, RemovalOfDeadNPCs) {
    std::vector<std::shared_ptr<NPC>> npcs;

    auto knight = Factory::createNPC("Knight", "Arthur", 0, 0);
    auto squirrel = Factory::createNPC("Squirrel", "Chip", 0, 0);
    auto pegasus = Factory::createNPC("Pegasus", "Wind", 0, 0);

    npcs.push_back(knight);
    npcs.push_back(squirrel);
    npcs.push_back(pegasus);

    auto observer = std::make_shared<ConsoleObserver>();
    for (auto& npc : npcs) {
        npc->attachObserver(observer);
    }

    // Рыцарь убивает Белку-шлюху
    squirrel->acceptInteraction(knight);

    // Удаляем мертвых NPC
    npcs.erase(std::remove_if(npcs.begin(), npcs.end(),
        [](const std::shared_ptr<NPC>& npc) { return !npc->isAlive(); }), npcs.end());

    EXPECT_EQ(npcs.size(), 2);
    EXPECT_EQ(npcs[0]->getType(), "Knight");
    EXPECT_EQ(npcs[1]->getType(), "Pegasus");
}

TEST(Battle_Tests, BothNPCsAliveAfterInteraction) {
    auto knight = Factory::createNPC("Knight", "Arthur", 0, 0);
    auto pegasus = Factory::createNPC("Pegasus", "Wind", 0, 0);
    auto observer = std::make_shared<ConsoleObserver>();
    knight->attachObserver(observer);
    pegasus->attachObserver(observer);

    // Пегас принимает в туза от Рыцаря
    knight->acceptInteraction(pegasus);

    EXPECT_TRUE(knight->isAlive());
    EXPECT_TRUE(pegasus->isAlive());
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
