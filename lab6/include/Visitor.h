#ifndef VISITOR_H
#define VISITOR_H

#include "Robber.h"
#include "Orc.h"
#include "Werewolf.h"

class Visitor {
public:
    virtual void visitRobber(Robber& robber, NPC& other) = 0;
    virtual void visitOrc(Orc& orc, NPC& other) = 0;
    virtual void visitWerewolf(Werewolf& werewolf, NPC& other) = 0;
    virtual ~Visitor() = default;
};

class BattleVisitor : public Visitor {
public:
    BattleVisitor(float range);
    void visitRobber(Robber& robber, NPC& other) override;
    void visitOrc(Orc& orc, NPC& other) override;
    void visitWerewolf(Werewolf& werewolf, NPC& other) override;

private:
    float combatRange;
};

#endif