#include "../include/observer.h"
#include "../include/logger.h"

void ConsoleObserver::onEvent(const std::string& event) {
    Logger::log(event);
}

FileObserver::FileObserver(const std::string& filename) {
    ofs.open(filename, std::ios::app);
}

FileObserver::~FileObserver() {
    if (ofs.is_open()) {
        ofs.close();
    }
}

void FileObserver::onEvent(const std::string& event) {
    std::lock_guard<std::mutex> lock(file_mutex);
    if (ofs.is_open()) {
        ofs << event << std::endl;
    }
}