#ifndef LOGGER_H
#define LOGGER_H

#include <unordered_map>
#include <string>

namespace Logger {
    extern std::unordered_map<std::string, bool> logLevels;

    void setLogLevel(const std::string& level, const bool enabled);

    auto currentTime() -> std::string;

    auto log(const std::string& level, const std::string& message) -> bool;
};

#endif