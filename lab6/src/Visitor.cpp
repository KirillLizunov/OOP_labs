#include "../include/Visitor.h"
#include "../include/NPC.h"

BattleVisitor::BattleVisitor(float range) : combatRange(range) {}

void BattleVisitor::visitRobber(Robber& robber, NPC& other) {
    if (!robber.isAlive() || !other.isAlive()) return;

    if (!NPC::isClose(robber, other, combatRange)) {
        return;
    }

    if (other.getTypeName() == "Werewolf") {
        robber.setAlive(false);
        other.setAlive(false);
        NPC::notify(robber.getName() + " и " + other.getName() + " убили друг друга.");
    } else if (other.getTypeName() == "Orc") {
        robber.setAlive(false);
        NPC::notify(other.getName() + " убил " + robber.getName());
    }
}

void BattleVisitor::visitOrc(Orc& orc, NPC& other) {
    if (!orc.isAlive() || !other.isAlive()) return;

    if (!NPC::isClose(orc, other, combatRange)) {
        return;
    }

    if (other.getTypeName() == "Robber") {
        other.setAlive(false);
        NPC::notify(orc.getName() + " убил " + other.getName());
    }
}

void BattleVisitor::visitWerewolf(Werewolf& werewolf, NPC& other) {
    if (!werewolf.isAlive() || !other.isAlive()) return;

    if (!NPC::isClose(werewolf, other, combatRange)) {
        return;
    }

    if (other.getTypeName() == "Robber") {
        other.setAlive(false);
        NPC::notify(werewolf.getName() + " убил " + other.getName());
    }
}