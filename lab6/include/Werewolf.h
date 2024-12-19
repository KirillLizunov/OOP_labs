#ifndef WEREWOLF_H
#define WEREWOLF_H

#include "NPC.h"

class Werewolf : public NPC {
public:
    Werewolf(const std::string& name, float x, float y);
    ~Werewolf() override;

    void accept(Visitor& visitor, NPC& other) override;
    std::string getTypeName() const override;

    void print() const override;

};

#endif