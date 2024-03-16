#ifndef __LOGGER_HPP__
#define __LOGGER_HPP__

#include <iostream>
#include <chrono>
#include "fmt/format.h"

class Logger
{
private:
    std::string getTimestamp()
    {
        std::time_t now = std::time(0);
        return std::ctime(&now);
    }
public:
    inline void logInfo(std::string message)
    {
        std::cout << fmt::format("[INFO]<{}> {}", getTimestamp(), message) << std::endl;
    }
    inline void logWarning(std::string message)
    {
        std::cout << fmt::format("[WARNING]<{}> {}", getTimestamp(), message) << std::endl;
    }
    inline void logError(std::string message)
    {
        std::cout << fmt::format("[ERROR]<{}> {}", getTimestamp(), message) << std::endl;
    }
};

#endif // __LOGGER_HPP__