#include "../include/Orc.h"
#include "../include/Visitor.h"
#include <iostream>

Orc::Orc(const std::string& name, float x, float y, int strength)
    : NPC(name, x, y), strength_(strength) {}

Orc::~Orc() {}

void Orc::accept(Visitor& visitor, NPC& other) {
    visitor.visitOrc(*this, other);
}

std::string Orc::getTypeName() const {
    return "Orc";
}

void Orc::print() const {
    std::cout << "[Orc] " << name_
              << " (Strength: " << strength_ << ") at position ("
              << x_ << ", " << y_ << ")"
              << (isAlive() ? " is ready to battle!" : " has fallen in battle.") << std::endl;
}