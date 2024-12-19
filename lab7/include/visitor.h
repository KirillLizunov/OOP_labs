#ifndef VISITOR_H
#define VISITOR_H

#include <memory>

struct Robber;
struct Werewolf;
struct Orc;
struct NPC;

struct Visitor {
    NPC& attacker;
    bool attackerDies;
    bool defenderDies;

    Visitor(NPC& attacker);

    void visit(Robber& robber, std::shared_ptr<NPC> other);
    void visit(Werewolf& werewolf, std::shared_ptr<NPC> other);
    void visit(Orc& orc, std::shared_ptr<NPC> other);
};

#endif