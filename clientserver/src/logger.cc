#include "logger.h"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <iostream>

namespace Logger {
    std::unordered_map<std::string, bool> logLevels = {
        {"NETWORK", false},
        {"SERVER", false},
        {"DATABASE", false}
    };

    void setLogLevel(const std::string& level, const bool enabled) {
        logLevels[level] = enabled;
    }

    auto currentTime() -> std::string {
        auto now = std::chrono::system_clock::now();
        auto in_time = std::chrono::system_clock::to_time_t(now);
        std::tm buf{};
        localtime_r(&in_time, &buf); // Use localtime_s on Windows
        std::ostringstream oss;
        oss << std::put_time(&buf, "%Y-%m-%d %H:%M:%S");
        return oss.str();
    }

    auto log(const std::string& level, const std::string& message) -> bool {
        if (logLevels[level]) {
            std::cout << "[" << level << "]" 
                      << "[" << currentTime() << "] "
                      << message << std::endl;
            return true;
        }

        return false;
    }
}