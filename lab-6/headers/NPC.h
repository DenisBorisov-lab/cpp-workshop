#ifndef NPC_H
#define NPC_H

#include <string>
#include <memory>
#include <vector>

class Knight;
class Squirrel;
class Pegasus;
class Observer;

class NPC : public std::enable_shared_from_this<NPC> {
public:
    NPC(const std::string& name, double x, double y);
    virtual ~NPC() = default;

    // Метод для принятия взаимодействия от другого NPC
    virtual void acceptInteraction(const std::shared_ptr<NPC>& other);

    // Базовый метод взаимодействия
    virtual void interact(NPC& other) = 0;

    // Специфичные методы взаимодействия для каждого типа NPC
    virtual void interactWith(Knight& knight) = 0;
    virtual void interactWith(Squirrel& squirrel) = 0;
    virtual void interactWith(Pegasus& pegasus) = 0;

    virtual std::string getType() const = 0;

    std::string getName() const;
    double getX() const;
    double getY() const;

    bool isInRange(const std::shared_ptr<NPC>& other, double range) const;

    void attachObserver(const std::shared_ptr<Observer>& observer);
    void detachObserver(const std::shared_ptr<Observer>& observer);
    void notifyObservers(const std::string& message);

    // Методы для управления состоянием NPC
    void die();
    bool isAlive() const;

protected:
    std::string name_;
    double x_;
    double y_;
    std::vector<std::weak_ptr<Observer>> observers_;
    bool alive_;
};

#endif // NPC_H
