#include "../include/Werewolf.h"
#include "../include/Visitor.h"
#include <iostream>

Werewolf::Werewolf(const std::string& name, float x, float y)
    : NPC(name, x, y) {}

Werewolf::~Werewolf() {}

void Werewolf::accept(Visitor& visitor, NPC& other) {
    visitor.visitWerewolf(*this, other);
}

std::string Werewolf::getTypeName() const {
    return "Werewolf";
}

void Werewolf::print() const {
    std::cout << "[Werewolf] " << name_
              << " at position (" << x_ << ", " << y_ << ")"
              << (isAlive() ? " is howling at the moon." : " has been slain.") << std::endl;
}