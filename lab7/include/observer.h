#ifndef OBSERVER_H
#define OBSERVER_H

#include <string>
#include <iostream>
#include <fstream>
#include <memory>
#include <mutex>

struct Observer {
    virtual void onEvent(const std::string& event) = 0;
    virtual ~Observer() = default; 
};

struct ConsoleObserver : public Observer {
    void onEvent(const std::string& event) override;
};

struct FileObserver : public Observer {
    FileObserver(const std::string& filename);
    ~FileObserver();
    void onEvent(const std::string& event) override;

private:
    std::ofstream ofs;
    std::mutex file_mutex;
};

#endif