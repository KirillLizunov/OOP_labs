#include "robber.h"

Robber::Robber(const std::string& name, int x, int y)
    : NPC(NpcType::RobberType, name, x, y) {}

void Robber::accept(Visitor& visitor, std::shared_ptr<NPC> other) {
    visitor.visit(*this, other);
}

void Robber::print() const {
    if (alive) {
        std::cout << "Robber - Name: " << name
                  << ", Coordinates: (" << x << ", " << y << ")" << std::endl;
    }
}

void Robber::save(std::ostream& os) const {
    NPC::save(os);
}