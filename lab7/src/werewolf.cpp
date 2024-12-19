#include "werewolf.h"

Werewolf::Werewolf(const std::string& name, int x, int y)
    : NPC(NpcType::WerewolfType, name, x, y) {}

void Werewolf::accept(Visitor& visitor, std::shared_ptr<NPC> other) {
    visitor.visit(*this, other);
}

void Werewolf::print() const {
    if (alive) {
        std::cout << "Werewolf - Name: " << name
                  << ", Coordinates: (" << x << ", " << y << ")" << std::endl;
    }
}

void Werewolf::save(std::ostream& os) const {
    NPC::save(os);
}