#include "../include/Observer.h"

void ConsoleObserver::update(const std::string& event) {
    std::cout << "Событие: " << event << std::endl;
}

FileObserver::FileObserver(const std::string& filename)
    : logFile_(filename, std::ios::app) {}

FileObserver::~FileObserver() {
    if (logFile_.is_open()) {
        logFile_.close();
    }
}

void FileObserver::update(const std::string& event) {
    if (logFile_.is_open()) {
        logFile_ << "Событие: " << event << std::endl;
    }
}