#ifndef CONSOLEOBSERVER_H
#define CONSOLEOBSERVER_H

#include "Observer.h"
#include <iostream>

class ConsoleObserver : public Observer {
public:
    void update(const std::string& message) override;
};

#endif // CONSOLEOBSERVER_H
