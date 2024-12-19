#ifndef NPC_H
#define NPC_H

#include <string>
#include <vector>
#include <memory>
#include "Observer.h"

class Visitor;

class NPC {
public:
    NPC(const std::string& name, float x, float y);
    virtual ~NPC();

    const std::string& getName() const;
    float getX() const;
    float getY() const;

    virtual void accept(Visitor& visitor, NPC& other) = 0;
    virtual std::string getTypeName() const = 0;

    void setAlive(bool isAlive);
    bool isAlive() const;

    virtual void print() const;

    static void addObserver(Observer* observer);
    static void removeObserver(Observer* observer);
    static void notify(const std::string& event);

    static bool isNameUnique(const std::vector<std::unique_ptr<NPC>>& npcs, const std::string& name);
    static float calculateDistance(const NPC& npc1, const NPC& npc2);
    static bool isClose(const NPC& npc1, const NPC& npc2, float range);

protected:
    std::string name_;
    float x_;
    float y_;
    bool alive_;

private:
    static std::vector<Observer*> observers_;
};

#endif