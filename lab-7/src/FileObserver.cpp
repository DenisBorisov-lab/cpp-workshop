#include "FileObserver.h"

FileObserver::FileObserver(const std::string& filename) {
    file_.open(filename, std::ios::out | std::ios::app);
}

FileObserver::~FileObserver() {
    if (file_.is_open()) {
        file_.close();
    }
}

void FileObserver::update(const std::string& message) {
    if (file_.is_open()) {
        file_ << message << std::endl;
    }
}
