#include "npcfactory.h"
#include <stdexcept>

std::shared_ptr<NPC> NPCFactory::createNPC(NpcType type, const std::string& name, int x, int y) {
    switch (type) {
        case NpcType::RobberType:
            return std::make_shared<Robber>(name, x, y);
        case NpcType::WerewolfType:
            return std::make_shared<Werewolf>(name, x, y);
        case NpcType::OrcType:
            return std::make_shared<Orc>(name, x, y);
        default:
            throw std::invalid_argument("Unknown NPC type");
    }
}