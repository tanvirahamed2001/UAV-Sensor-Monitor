#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>

// Loads threshold configuration from a key=value config file at runtime.
// Falls back to safe defaults if file is missing or a key is absent.
class Config {
public:
    float minAltitude    = 15.0f;
    float maxTemperature = 70.0f;
    float minBattery     = 10.0f;
    int   totalTicks     = 30;

    Config() {}

    Config(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cout << "[CONFIG] config.txt not found — using default thresholds." << std::endl;
            return;
        }

        std::map<std::string, std::string> values;
        std::string line;
        while (std::getline(file, line)) {
            // Skip comments and blank lines
            if (line.empty() || line[0] == '#') continue;
            std::istringstream ss(line);
            std::string key, val;
            if (std::getline(ss, key, '=') && std::getline(ss, val)) {
                values[key] = val;
            }
        }

        if (values.count("MIN_ALTITUDE"))    minAltitude    = std::stof(values["MIN_ALTITUDE"]);
        if (values.count("MAX_TEMPERATURE")) maxTemperature = std::stof(values["MAX_TEMPERATURE"]);
        if (values.count("MIN_BATTERY"))     minBattery     = std::stof(values["MIN_BATTERY"]);
        if (values.count("TOTAL_TICKS"))     totalTicks     = std::stoi(values["TOTAL_TICKS"]);

        std::cout << "[CONFIG] Loaded thresholds from config.txt" << std::endl;
        std::cout << "  MIN_ALTITUDE    = " << minAltitude    << "m"  << std::endl;
        std::cout << "  MAX_TEMPERATURE = " << maxTemperature << "C"  << std::endl;
        std::cout << "  MIN_BATTERY     = " << minBattery     << "%"  << std::endl;
        std::cout << "  TOTAL_TICKS     = " << totalTicks            << std::endl;
    }
};
