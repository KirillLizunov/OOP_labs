#include "../include/NPC.h"
#include <cmath>
#include <algorithm>
#include <iostream>

std::vector<Observer*> NPC::observers_;

NPC::NPC(const std::string& name, float x, float y)
    : name_(name), x_(x), y_(y), alive_(true) {}

NPC::~NPC() {}

const std::string& NPC::getName() const {
    return name_;
}

float NPC::getX() const {
    return x_;
}

float NPC::getY() const {
    return y_;
}

void NPC::setAlive(bool isAlive) {
    alive_ = isAlive;
}

bool NPC::isAlive() const {
    return alive_;
}

void NPC::print() const {
    std::cout << getTypeName() << " " << name_
              << " (" << x_ << ", " << y_ << ")"
              << (isAlive() ? " [Alive]" : " [Dead]") << std::endl;
}

void NPC::addObserver(Observer* observer) {
    observers_.push_back(observer);
}

void NPC::removeObserver(Observer* observer) {
    observers_.erase(
        std::remove(observers_.begin(), observers_.end(), observer),
        observers_.end()
    );
}

void NPC::notify(const std::string& event) {
    for (auto observer : observers_) {
        observer->update(event);
    }
}

bool NPC::isNameUnique(const std::vector<std::unique_ptr<NPC>>& npcs, const std::string& name) {
    for (const auto& npc : npcs) {
        if (npc->getName() == name) {
            return false;
        }
    }
    return true;
}

float NPC::calculateDistance(const NPC& npc1, const NPC& npc2) {
    float dx = npc1.getX() - npc2.getX();
    float dy = npc1.getY() - npc2.getY();
    return std::sqrt(dx * dx + dy * dy);
}

bool NPC::isClose(const NPC& npc1, const NPC& npc2, float range) {
    return calculateDistance(npc1, npc2) <= range;
}