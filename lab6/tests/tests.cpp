#include <gtest/gtest.h>
#include "../include/NPCFactory.h"
#include "../include/Robber.h"
#include "../include/Orc.h"
#include "../include/Werewolf.h"
#include "../include/Visitor.h"
#include "../include/Observer.h"

TEST(NPCCreationTest, CreateRobber) {
    NPCFactory& factory = NPCFactory::getInstance();
    factory.registerType("Robber", [](const std::string& name, float x, float y) {
        return std::make_unique<Robber>(name, x, y);
    });

    auto npc = factory.createNPC("Robber", "Killer", 100.0f, 200.0f);
    EXPECT_EQ(npc->getTypeName(), "Robber");
    EXPECT_EQ(npc->getName(), "Killer");
    EXPECT_FLOAT_EQ(npc->getX(), 100.0f);
    EXPECT_FLOAT_EQ(npc->getY(), 200.0f);
}

TEST(NPCCreationTest, CreateOrc) {
    NPCFactory& factory = NPCFactory::getInstance();
    factory.registerType("Orc", [](const std::string& name, float x, float y) {
        return std::make_unique<Orc>(name, x, y, 10);
    });

    auto npc = factory.createNPC("Orc", "Gor", 150.0f, 250.0f);
    EXPECT_EQ(npc->getTypeName(), "Orc");
    EXPECT_EQ(npc->getName(), "Gor");
    EXPECT_FLOAT_EQ(npc->getX(), 150.0f);
    EXPECT_FLOAT_EQ(npc->getY(), 250.0f);
}

TEST(NPCCreationTest, CreateWerewolf) {
    NPCFactory& factory = NPCFactory::getInstance();
    factory.registerType("Werewolf", [](const std::string& name, float x, float y) {
        return std::make_unique<Werewolf>(name, x, y);
    });

    auto npc = factory.createNPC("Werewolf", "Lupin", 200.0f, 300.0f);
    EXPECT_EQ(npc->getTypeName(), "Werewolf");
    EXPECT_EQ(npc->getName(), "Lupin");
    EXPECT_FLOAT_EQ(npc->getX(), 200.0f);
    EXPECT_FLOAT_EQ(npc->getY(), 300.0f);
}

TEST(NPCCreationTest, UniqueNameTest) {
    std::vector<std::unique_ptr<NPC>> npcs;
    npcs.push_back(std::make_unique<Robber>("Jack", 100.0f, 200.0f));

    EXPECT_FALSE(NPC::isNameUnique(npcs, "Jack"));
    EXPECT_TRUE(NPC::isNameUnique(npcs, "John"));
}

TEST(DistanceTest, CalculateDistance) {
    Robber robber("Jack", 0.0f, 0.0f);
    Orc orc("Gor", 3.0f, 4.0f, 10);

    float distance = NPC::calculateDistance(robber, orc);
    EXPECT_FLOAT_EQ(distance, 5.0f);
}

TEST(DistanceTest, IsClose) {
    Robber robber("Jack", 0.0f, 0.0f);
    Orc orc("Gor", 1.0f, 1.0f, 10);

    EXPECT_TRUE(NPC::isClose(robber, orc, 2.0f));
    EXPECT_FALSE(NPC::isClose(robber, orc, 1.0f));
}

class MockObserver : public Observer {
public:
    void update(const std::string& event) override {
        events.push_back(event);
    }
    std::vector<std::string> events;
};

TEST(CombatTest, NoCombatWhenFar) {
    Robber robber("Jack", 0.0f, 0.0f);
    Orc orc("Gor", 100.0f, 100.0f, 10);
    float combatRange = 10.0f;
    BattleVisitor visitor(combatRange);

    MockObserver observer;
    NPC::addObserver(&observer);

    robber.accept(visitor, orc);

    EXPECT_TRUE(robber.isAlive());
    EXPECT_TRUE(orc.isAlive());
    EXPECT_TRUE(observer.events.empty());

    NPC::removeObserver(&observer);
}


TEST(CombatTest, RobberVsWerewolf) {
    Robber robber("Jack", 0.0f, 0.0f);
    Werewolf werewolf("Lupin", 0.0f, 0.0f);
    float combatRange = 10.0f;
    BattleVisitor visitor(combatRange);

    MockObserver observer;
    NPC::addObserver(&observer);

    robber.accept(visitor, werewolf);

    EXPECT_FALSE(robber.isAlive());
    EXPECT_FALSE(werewolf.isAlive());
    EXPECT_EQ(observer.events.size(), 1);
    EXPECT_EQ(observer.events[0], "Jack и Lupin убили друг друга.");

    NPC::removeObserver(&observer);
}

TEST(CombatTest, OrcKillsRobber) {
    Orc orc("Gor", 0.0f, 0.0f, 10);
    Robber robber("Jack", 0.0f, 0.0f);
    float combatRange = 10.0f;
    BattleVisitor visitor(combatRange);

    MockObserver observer;
    NPC::addObserver(&observer);

    orc.accept(visitor, robber);

    EXPECT_TRUE(orc.isAlive());
    EXPECT_FALSE(robber.isAlive());
    EXPECT_EQ(observer.events.size(), 1);
    EXPECT_EQ(observer.events[0], "Gor убил Jack");

    NPC::removeObserver(&observer);
}

TEST(CombatTest, WerewolfKillsRobber) {
    Werewolf werewolf("Lupin", 0.0f, 0.0f);
    Robber robber("Jack", 0.0f, 0.0f);
    float combatRange = 10.0f;
    BattleVisitor visitor(combatRange);

    MockObserver observer;
    NPC::addObserver(&observer);

    werewolf.accept(visitor, robber);

    EXPECT_TRUE(werewolf.isAlive());
    EXPECT_FALSE(robber.isAlive());
    EXPECT_EQ(observer.events.size(), 1);
    EXPECT_EQ(observer.events[0], "Lupin убил Jack");

    NPC::removeObserver(&observer);
}

TEST(ObserverTest, ConsoleObserverTest) {
    ConsoleObserver consoleObserver;
    testing::internal::CaptureStdout();

    consoleObserver.update("Test Event");

    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Событие: Test Event\n");
}

TEST(ObserverTest, FileObserverTest) {
    std::string filename = "test_log.txt";
    {
        FileObserver fileObserver(filename);
        fileObserver.update("Test Event");
    }
    std::ifstream file(filename);
    ASSERT_TRUE(file.is_open());

    std::string line;
    std::getline(file, line);
    EXPECT_EQ(line, "Событие: Test Event");

    file.close();
    std::remove(filename.c_str());
}

TEST(ObserverTest, MockObserverTest) {
    MockObserver observer;
    NPC::addObserver(&observer);

    NPC::notify("Event 1");
    NPC::notify("Event 2");

    EXPECT_EQ(observer.events.size(), 2);
    EXPECT_EQ(observer.events[0], "Event 1");
    EXPECT_EQ(observer.events[1], "Event 2");

    NPC::removeObserver(&observer);
}

TEST(SaveLoadTest, SaveAndLoadNPCs) {
    NPCFactory& factory = NPCFactory::getInstance();
    factory.registerType("Robber", [](const std::string& name, float x, float y) {
        return std::make_unique<Robber>(name, x, y);
    });
    factory.registerType("Orc", [](const std::string& name, float x, float y) {
        return std::make_unique<Orc>(name, x, y, 10);
    });
    factory.registerType("Werewolf", [](const std::string& name, float x, float y) {
        return std::make_unique<Werewolf>(name, x, y);
    });

    std::vector<std::unique_ptr<NPC>> npcs;
    npcs.push_back(factory.createNPC("Robber", "Jack", 100.0f, 200.0f));
    npcs.push_back(factory.createNPC("Orc", "Gor", 150.0f, 250.0f));
    npcs.push_back(factory.createNPC("Werewolf", "Lupin", 200.0f, 300.0f));

    std::string filename = "test_npcs.txt";
    factory.saveNPCs(npcs, filename);

    auto loadedNPCs = factory.loadNPCs(filename);

    EXPECT_EQ(loadedNPCs.size(), 3);
    EXPECT_EQ(loadedNPCs[0]->getName(), "Jack");
    EXPECT_EQ(loadedNPCs[1]->getName(), "Gor");
    EXPECT_EQ(loadedNPCs[2]->getName(), "Lupin");

    std::remove(filename.c_str());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}