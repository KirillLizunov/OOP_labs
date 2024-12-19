#ifndef NPCFACTORY_H
#define NPCFACTORY_H

#include "NPC.h"
#include <functional>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <memory>

class NPCFactory {
public:
    using Creator = std::function<std::unique_ptr<NPC>(const std::string&, float, float)>;

    static NPCFactory& getInstance();

    void registerType(const std::string& typeName, Creator creator);
    std::unique_ptr<NPC> createNPC(const std::string& typeName, const std::string& name, float x, float y);

    void saveNPCs(const std::vector<std::unique_ptr<NPC>>& npcs, const std::string& filename);
    std::vector<std::unique_ptr<NPC>> loadNPCs(const std::string& filename);

private:
    NPCFactory() = default;
    std::unordered_map<std::string, Creator> creators_;
};

#endif