#ifndef LOGGER_H
#define LOGGER_H

#include <mutex>
#include <string>
#include <iostream>

class Logger {
public:
    static void log(const std::string& message);

    template<typename T>
    static void log(const T& data) {
        std::lock_guard<std::mutex> lock(console_mutex);
        std::cout << data << std::endl;
    }

    template<typename... Args>
    static void log(const Args&... args) {
        std::lock_guard<std::mutex> lock(console_mutex);
        (std::cout << ... << args) << std::endl;
    }

    template<typename Func>
    static void logBlock(Func func) {
        std::lock_guard<std::mutex> lock(console_mutex);
        func();
    }

private:
    static std::mutex console_mutex;
};

#endif