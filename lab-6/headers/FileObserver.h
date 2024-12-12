#ifndef FILEOBSERVER_H
#define FILEOBSERVER_H

#include "Observer.h"
#include <fstream>

class FileObserver : public Observer {
public:
    FileObserver(const std::string& filename);
    ~FileObserver();
    void update(const std::string& message) override;

private:
    std::ofstream file_;
};

#endif // FILEOBSERVER_H
