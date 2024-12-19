#include "include/npc.h"
#include "include/npcfactory.h"
#include "include/observer.h"
#include "include/logger.h"
#include "include/scheduler.h"
#include "include/robber.h"
#include "include/orc.h"
#include "include/werewolf.h"
#include <iostream>
#include <vector>
#include <atomic>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <ctime>

std::vector<std::shared_ptr<NPC>> npcs;
std::atomic<bool> game_over(false);

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    auto consoleObserver = std::make_shared<ConsoleObserver>();
    auto fileObserver = std::make_shared<FileObserver>("log.txt");

    const int num_npcs = 8;
    for (int i = 0; i < num_npcs; ++i) {
        NpcType type = static_cast<NpcType>(std::rand() % 3 + 1);
        std::string name = "NPC_" + std::to_string(i);
        int x = std::rand() % 501;
        int y = std::rand() % 501;

        auto npc = NPCFactory::createNPC(type, name, x, y);
        npc->addObserver(consoleObserver);
        npc->addObserver(fileObserver);

        npcs.push_back(npc);
    }

    for (auto& npc : npcs) {
        Scheduler::instance().schedule(npc->run());
    }

    std::thread scheduler_thread([]() {
        while (!game_over) {
            Scheduler::instance().run();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    });

    auto start_time = std::chrono::steady_clock::now();
    while (!game_over) {
        Logger::logBlock([&]() {
            std::cout << "Current NPC positions:" << std::endl;
            for (const auto& npc : npcs) {
                if (npc->alive) {
                    npc->print();
                }
            }
            std::cout << "-------------------------------------" << std::endl;
        });

        std::this_thread::sleep_for(std::chrono::seconds(1));

        auto elapsed = std::chrono::steady_clock::now() - start_time;
        if (std::chrono::duration_cast<std::chrono::seconds>(elapsed).count() >= 0.1) {
            game_over = true;
        }
    }

    scheduler_thread.join();

    Logger::log("Game over! Survivors:");
    for (const auto& npc : npcs) {
        if (npc->alive) {
            npc->print();
        }
    }

    return 0;
}