#include <gtest/gtest.h>
#include <memory>
#include <vector>
#include <atomic>
#include <sstream>
#include "../include/npc.h"
#include "../include/robber.h"
#include "../include/orc.h"
#include "../include/werewolf.h"
#include "../include/visitor.h"
#include "../include/observer.h"
#include "../include/npcfactory.h"
#include "../include/scheduler.h"

std::vector<std::shared_ptr<NPC>> npcs;
std::atomic<bool> game_over(false);

class NPCTest : public ::testing::Test {
protected:
    void SetUp() override {
        auto robber = NPCFactory::createNPC(NpcType::RobberType, "TestRobber", 10, 10);
        auto werewolf = NPCFactory::createNPC(NpcType::WerewolfType, "TestWerewolf", 20, 20);
        auto orc = NPCFactory::createNPC(NpcType::OrcType, "TestOrc", 30, 30);
        
        npcs.push_back(robber);
        npcs.push_back(werewolf);
        npcs.push_back(orc);
    }
    
    void TearDown() override {
        npcs.clear();
        game_over.store(false);
    }
};

TEST_F(NPCTest, CreationTest) {
    ASSERT_EQ(npcs.size(), 3);

    EXPECT_EQ(npcs[0]->name, "TestRobber");
    EXPECT_EQ(npcs[1]->name, "TestWerewolf");
    EXPECT_EQ(npcs[2]->name, "TestOrc");

    EXPECT_EQ(npcs[0]->x, 10);
    EXPECT_EQ(npcs[0]->y, 10);
    EXPECT_EQ(npcs[1]->x, 20);
    EXPECT_EQ(npcs[1]->y, 20);
    EXPECT_EQ(npcs[2]->x, 30);
    EXPECT_EQ(npcs[2]->y, 30);
}

TEST_F(NPCTest, Movement) {
    auto initial_x = npcs[0]->x;
    auto initial_y = npcs[0]->y;

    auto task = npcs[0]->run();
    Scheduler::instance().schedule(std::move(task));
    Scheduler::instance().run();

    EXPECT_NE(npcs[0]->x, initial_x);
    EXPECT_NE(npcs[0]->y, initial_y);
}

TEST_F(NPCTest, Interaction) {
    npcs[0]->x = 0;
    npcs[0]->y = 0;

    npcs[1]->x = 0;
    npcs[1]->y = 0;

    auto task1 = npcs[0]->run();
    auto task2 = npcs[1]->run();
    Scheduler::instance().schedule(std::move(task1));
    Scheduler::instance().schedule(std::move(task2));

    for (int i = 0; i < 10; ++i) {
        Scheduler::instance().run();
    }

    bool robber_alive = npcs[0]->alive;
    bool werewolf_alive = npcs[1]->alive;

    EXPECT_TRUE(robber_alive && !werewolf_alive)
        << "Robber should survive and Werewolf should die.";
}


TEST_F(NPCTest, GameOver) {
    game_over.store(true);

    auto task = npcs[0]->run();
    Scheduler::instance().schedule(std::move(task));
    Scheduler::instance().run();

    EXPECT_TRUE(task.done());
}


TEST_F(NPCTest, DistanceTest) {
    auto npc1 = npcs[0];
    auto npc2 = NPCFactory::createNPC(NpcType::WerewolfType, "Werewolf1", 13, 14);

    EXPECT_TRUE(npc1->isClose(npc2, 5));
    EXPECT_FALSE(npc1->isClose(npc2, 4));
}


TEST_F(NPCTest, FightTest) {
    auto robber = npcs[0];
    auto werewolf = npcs[1];
    auto orc = npcs[2];

    Visitor fight1(*robber);
    werewolf->accept(fight1, robber);
    EXPECT_TRUE(fight1.defenderDies);

    Visitor fight2(*werewolf);
    robber->accept(fight2, werewolf);
    EXPECT_TRUE(fight2.defenderDies);

    Visitor fight3(*orc);
    robber->accept(fight3, orc);
    EXPECT_TRUE(fight3.defenderDies);
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}