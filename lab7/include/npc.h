#ifndef NPC_H
#define NPC_H

#include <iostream>
#include <memory>
#include <vector>
#include <mutex>
#include <shared_mutex>
#include "visitor.h"
#include "observer.h"
#include "task.h"

enum class NpcType {
    RobberType = 1,
    WerewolfType = 2,
    OrcType = 3
};

struct NPC : public std::enable_shared_from_this<NPC> {
    NpcType type;
    std::string name;
    int x, y;
    int move_distance;
    int kill_distance;
    bool alive;

    NPC(NpcType type, const std::string& name, int x, int y);
    virtual ~NPC() = default;

    virtual void accept(Visitor& visitor, std::shared_ptr<NPC> other) = 0;
    virtual void print() const;
    virtual void save(std::ostream& os) const;

    void addObserver(std::shared_ptr<Observer> observer);
    void notify(const std::string& event);

    bool isClose(const std::shared_ptr<NPC>& other, size_t distance) const;

    Task run();

    static std::shared_ptr<NPC> load(std::istream& is);

private:
    std::vector<std::weak_ptr<Observer>> observers;
};

#endif