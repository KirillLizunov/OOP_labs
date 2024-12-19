#include "../include/Robber.h"
#include "../include/Visitor.h"
#include <iostream>

Robber::Robber(const std::string& name, float x, float y)
    : NPC(name, x, y) {}

Robber::~Robber() {}

void Robber::accept(Visitor& visitor, NPC& other) {
    visitor.visitRobber(*this, other);
}

std::string Robber::getTypeName() const {
    return "Robber";
}

void Robber::print() const {
    std::cout << "[Robber] " << name_
              << " at position (" << x_ << ", " << y_ << ")"
              << (isAlive() ? " is lurking..." : " has been defeated.") << std::endl;
}