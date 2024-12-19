#include "../include/npc.h"
#include "../include/npcfactory.h"
#include "../include/logger.h"
#include "../include/scheduler.h"
#include <random>
#include <iostream>
#include <atomic>
#include <algorithm>


extern std::vector<std::shared_ptr<NPC>> npcs;
extern std::atomic<bool> game_over;

NPC::NPC(NpcType type, const std::string& name, int x, int y)
    : type(type), name(name), x(x), y(y), alive(true) {
    switch (type) {
        case NpcType::RobberType:
            move_distance = 10;
            kill_distance = 10;
            break;
        case NpcType::WerewolfType:
            move_distance = 40;
            kill_distance = 5;
            break;
        case NpcType::OrcType:
            move_distance = 20;
            kill_distance = 10;
            break;
        default:
            move_distance = 0;
            kill_distance = 0;
            break;
    }
}

void NPC::addObserver(std::shared_ptr<Observer> observer) {
    observers.push_back(observer);
}

void NPC::notify(const std::string& event) {
    for (auto& weakObs : observers) {
        if (auto obs = weakObs.lock()) {
            obs->onEvent(event);
        }
    }
}

bool NPC::isClose(const std::shared_ptr<NPC>& other, size_t distance) const {
    int dx = x - other->x;
    int dy = y - other->y;
    return (dx * dx + dy * dy) <= (distance * distance);
}

void NPC::print() const {
    if (alive) {
        std::cout << "Type: " << static_cast<int>(type)
                  << ", Name: " << name
                  << ", Coordinates: (" << x << ", " << y << ")" << std::endl;
    }
}

void NPC::save(std::ostream& os) const {
    os << static_cast<int>(type) << ' ' << name << ' ' << x << ' ' << y << ' ' << alive << '\n';
}

Task NPC::run() {
    static thread_local std::default_random_engine generator(std::random_device{}());
    std::uniform_int_distribution<int> dice_distribution(1, 6);
    std::uniform_int_distribution<int> move_distribution(-move_distance, move_distance);

    while (alive && !game_over.load()) {
        x += move_distribution(generator);
        y += move_distribution(generator);
        x = std::clamp(x, 0, 100);
        y = std::clamp(y, 0, 100);

        std::cout << "NPC " << name << " moved to (" << x << ", " << y << ").\n";

        for (auto& other : npcs) {
            if (other.get() == this || !other->alive) continue;

            if (isClose(other, kill_distance)) {
                Visitor fight(*this);
                other->accept(fight, shared_from_this());

                std::cout << "NPC " << name << " fights with " << other->name << ".\n";
                std::cout << "AttackerDies: " << fight.attackerDies
                          << ", DefenderDies: " << fight.defenderDies << "\n";

                if (fight.defenderDies) {
                    other->alive = false;
                    other->notify(other->name + " was killed by " + name);
                }
                if (fight.attackerDies) {
                    alive = false;
                    notify(name + " was killed by " + other->name);
                    co_return;
                }
            }
        }

        co_await std::suspend_always{};
    }
}


std::shared_ptr<NPC> NPC::load(std::istream& is) {
    int typeInt;
    std::string name;
    int x, y;
    bool alive;
    if (!(is >> typeInt >> name >> x >> y >> alive)) {
        return nullptr;
    }

    NpcType type = static_cast<NpcType>(typeInt);
    auto npc = NPCFactory::createNPC(type, name, x, y);
    npc->alive = alive;
    return npc;
}