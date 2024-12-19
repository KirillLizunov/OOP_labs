#include "visitor.h"
#include "robber.h"
#include "werewolf.h"
#include "orc.h"
#include <iostream>

Visitor::Visitor(NPC& attacker)
    : attacker(attacker), attackerDies(false), defenderDies(false) {}

void Visitor::visit(Robber& robber, std::shared_ptr<NPC> other) {
    std::cout << "Visitor::visit(Robber, NPC)" << std::endl;
    std::cout << "Attacker Type: " << static_cast<int>(attacker.type)
              << ", Defender Type: " << static_cast<int>(robber.type) << std::endl;

    if (attacker.type == NpcType::WerewolfType) {
        defenderDies = true;
    } else if (attacker.type == NpcType::OrcType) {
        defenderDies = true;
    }
}

void Visitor::visit(Werewolf& werewolf, std::shared_ptr<NPC> other) {
    std::cout << "Visitor::visit(Werewolf, NPC)" << std::endl;
    std::cout << "Attacker Type: " << static_cast<int>(attacker.type)
              << ", Defender Type: " << static_cast<int>(werewolf.type) << std::endl;

    if (attacker.type == NpcType::RobberType) {
        defenderDies = true;
    }
}

void Visitor::visit(Orc& orc, std::shared_ptr<NPC> other) {
    std::cout << "Visitor::visit(Orc, NPC)" << std::endl;
    std::cout << "Attacker Type: " << static_cast<int>(attacker.type)
              << ", Defender Type: " << static_cast<int>(orc.type) << std::endl;

    if (attacker.type == NpcType::RobberType) {
        defenderDies = true;
    }
}