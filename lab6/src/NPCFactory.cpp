#include "../include/NPCFactory.h"
#include <iostream>

NPCFactory& NPCFactory::getInstance() {
    static NPCFactory instance;
    return instance;
}

void NPCFactory::registerType(const std::string& typeName, Creator creator) {
    creators_[typeName] = creator;
}

std::unique_ptr<NPC> NPCFactory::createNPC(const std::string& typeName, const std::string& name, float x, float y) {
    if (creators_.find(typeName) != creators_.end()) {
        return creators_[typeName](name, x, y);
    }
    throw std::runtime_error("Unknown NPC type: " + typeName);
}

void NPCFactory::saveNPCs(const std::vector<std::unique_ptr<NPC>>& npcs, const std::string& filename) {
    std::ofstream file(filename);
    for (const auto& npc : npcs) {
        file << npc->getTypeName() << " " << npc->getName() << " "
             << npc->getX() << " " << npc->getY() << "\n";
    }
}

std::vector<std::unique_ptr<NPC>> NPCFactory::loadNPCs(const std::string& filename) {
    std::vector<std::unique_ptr<NPC>> npcs;
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string typeName, name;
        float x, y;
        iss >> typeName >> name >> x >> y;
        try {
            auto npc = createNPC(typeName, name, x, y);
            npcs.push_back(std::move(npc));
        } catch (const std::exception& e) {
            std::cout << e.what() << "\n";
        }
    }
    return npcs;
}