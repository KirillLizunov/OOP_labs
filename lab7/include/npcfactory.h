#ifndef NPCFACTORY_H
#define NPCFACTORY_H

#include "npc.h"
#include "robber.h"
#include "werewolf.h"
#include "orc.h"
#include <memory>

struct NPCFactory {
    static std::shared_ptr<NPC> createNPC(NpcType type, const std::string& name, int x, int y);
};

#endif