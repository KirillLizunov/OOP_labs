#include "../include/orc.h"
#include "../include/visitor.h"

Orc::Orc(const std::string& name, int x, int y)
    : NPC(NpcType::OrcType, name, x, y) {}

void Orc::accept(Visitor& visitor, std::shared_ptr<NPC> other) {
    visitor.visit(*this, other);
}

void Orc::print() const {
    if (alive) {
        std::cout << "Orc - Name: " << name
                  << ", Coordinates: (" << x << ", " << y << ")" << std::endl;
    }
}

void Orc::save(std::ostream& os) const {
    NPC::save(os);
}