#include "include/NPCFactory.h"
#include "include/Visitor.h"
#include "include/Observer.h"
#include "include/Robber.h"
#include "include/Orc.h"
#include "include/Werewolf.h"
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <limits>

void printNPCs(const std::vector<std::unique_ptr<NPC>>& npcs) {
    for (const auto& npc : npcs) {
        npc->print();
    }
}

int main() {
    NPCFactory& factory = NPCFactory::getInstance();

    factory.registerType("Robber", [](const std::string& name, float x, float y) {
        return std::make_unique<Robber>(name, x, y);
    });
    factory.registerType("Orc", [](const std::string& name, float x, float y) {
        int strength;
        std::cout << "Введите силу Orc: ";
        std::cin >> strength;
        return std::make_unique<Orc>(name, x, y, strength);
    });
    factory.registerType("Werewolf", [](const std::string& name, float x, float y) {
        return std::make_unique<Werewolf>(name, x, y);
    });

    float range;
    std::cout << "Введите дальность сражения: ";
    std::cin >> range;

    BattleVisitor battleVisitor(range);

    std::vector<std::unique_ptr<NPC>> npcs;
    ConsoleObserver consoleObserver;
    FileObserver fileObserver("log.txt");

    NPC::addObserver(&consoleObserver);
    NPC::addObserver(&fileObserver);

    while (true) {
        std::cout << "\nМеню:\n"
                  << "1. Добавить нового NPC\n"
                  << "2. Сохранить NPC в файл\n"
                  << "3. Загрузить NPC из файла\n"
                  << "4. Показать всех NPC\n"
                  << "5. Запустить боевой режим\n"
                  << "6. Выход\n"
                  << "Выберите действие: ";
        int choice;
        std::cin >> choice;

        if (choice == 1) {
            std::string typeName, name;
            float x, y;

            std::cout << "Введите тип NPC (Robber, Orc, Werewolf): ";
            std::cin >> typeName;

            std::cout << "Введите имя NPC: ";
            std::cin >> name;

            if (!NPC::isNameUnique(npcs, name)) {
                std::cout << "Имя уже занято. Попробуйте другое имя.\n";
                continue;
            }

            std::cout << "Введите координаты x и y (0 <= x <= 500, 0 <= y <= 500): ";
            std::cin >> x >> y;

            if (x < 0 || x > 500 || y < 0 || y > 500) {
                std::cout << "Координаты вне допустимого диапазона.\n";
                continue;
            }

            try {
                auto npc = factory.createNPC(typeName, name, x, y);
                npcs.push_back(std::move(npc));
                std::cout << "NPC добавлен успешно.\n";
            } catch (const std::exception& e) {
                std::cout << e.what() << "\n";
            }

        } else if (choice == 2) {
            std::string filename;
            std::cout << "Введите имя файла для сохранения: ";
            std::cin >> filename;
            factory.saveNPCs(npcs, filename);
            std::cout << "NPC сохранены в файл " << filename << ".\n";

        } else if (choice == 3) {
            std::string filename;
            std::cout << "Введите имя файла для загрузки: ";
            std::cin >> filename;
            auto loadedNPCs = factory.loadNPCs(filename);
            npcs.insert(npcs.end(),
                        std::make_move_iterator(loadedNPCs.begin()),
                        std::make_move_iterator(loadedNPCs.end()));
            std::cout << "NPC загружены из файла " << filename << ".\n";

        } else if (choice == 4) {
            printNPCs(npcs);

        } else if (choice == 5) {
            float range;
            std::cout << "Введите дальность сражения: ";
            std::cin >> range;

            bool someoneFought = true;
            while (someoneFought) {
                someoneFought = false;
                for (auto& npc1 : npcs) {
                    if (!npc1->isAlive()) continue;
                    for (auto& npc2 : npcs) {
                        if (!npc2->isAlive() || npc1.get() == npc2.get()) continue;
                        if (NPC::isClose(*npc1, *npc2, range)) {
                            npc1->accept(battleVisitor, *npc2);
                            someoneFought = true;
                        }
                    }
                }
            }

            npcs.erase(
                std::remove_if(npcs.begin(), npcs.end(),
                               [](const std::unique_ptr<NPC>& npc) { return !npc->isAlive(); }),
                npcs.end()
            );

            std::cout << "Боевой режим завершен.\n";

        } else if (choice == 6) {
            break;

        } else {
            std::cout << "Неверный выбор. Попробуйте снова.\n";
        }
    }

    NPC::removeObserver(&consoleObserver);
    NPC::removeObserver(&fileObserver);

    return 0;
}