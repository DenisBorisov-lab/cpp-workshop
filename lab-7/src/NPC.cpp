#include "NPC.h"
#include "Observer.h"

NPC::NPC(const std::string& name, double x, double y)
    : name_(name), x_(x), y_(y), alive_(true) {}

std::string NPC::getName() const {
    return name_;
}

double NPC::getX() const {
    return x_;
}

double NPC::getY() const {
    return y_;
}

bool NPC::isInRange(const std::shared_ptr<NPC>& other, double range) const {
    double dx = x_ - other->getX();
    double dy = y_ - other->getY();
    return std::sqrt(dx * dx + dy * dy) <= range;
}

void NPC::attachObserver(const std::shared_ptr<Observer>& observer) {
    observers_.push_back(observer);
}

void NPC::detachObserver(const std::shared_ptr<Observer>& observer) {
    observers_.erase(std::remove_if(observers_.begin(), observers_.end(),
        [&observer](const std::weak_ptr<Observer>& o) {
            return o.lock() == observer;
        }), observers_.end());
}

void NPC::notifyObservers(const std::string& message) {
    for (auto it = observers_.begin(); it != observers_.end();) {
        if (auto obs = it->lock()) {
            obs->update(message);
            ++it;
        } else {
            it = observers_.erase(it);
        }
    }
}

void NPC::die() {
    alive_ = false;
}

bool NPC::isAlive() const {
    return alive_;
}

void NPC::acceptInteraction(const std::shared_ptr<NPC>& other) {
    if (!this->isAlive() || !other->isAlive()) {
        return;
    }
    this->interact(*other);
}

void NPC::setPosition(double x, double y) {
    x_ = x;
    y_ = y;
}
