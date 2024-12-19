#include "../include/logger.h"

std::mutex Logger::console_mutex;

void Logger::log(const std::string& message) {
    std::lock_guard<std::mutex> lock(console_mutex);
    std::cout << message << std::endl;
}