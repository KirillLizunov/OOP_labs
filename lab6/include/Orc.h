#ifndef ORC_H
#define ORC_H

#include "NPC.h"

class Orc : public NPC {
public:
    Orc(const std::string& name, float x, float y, int strength);
    ~Orc() override;

    void accept(Visitor& visitor, NPC& other) override;
    std::string getTypeName() const override;

    void print() const override;

private:
    int strength_;
};

#endif