#ifndef ORC_H
#define ORC_H

#include "npc.h"

struct Orc : public NPC {
    Orc(const std::string& name, int x, int y);
    ~Orc() override = default;

    void accept(Visitor& visitor, std::shared_ptr<NPC> other) override;
    void print() const override;
    void save(std::ostream& os) const override;
};

#endif