#pragma once
#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <algorithm>

// Tracks fault history across the entire flight session.
// Records frequency per fault type and timestamps of each occurrence.
class FaultStats {
private:
    std::map<std::string, int> faultCount;
    std::vector<std::pair<int, std::string>> faultLog; // {tick, fault}

public:
    void record(int tick, const std::string& fault) {
        if (fault.empty()) return;

        // Categorize by fault type
        std::string category = categorize(fault);
        faultCount[category]++;
        faultLog.push_back({tick, fault});
    }

    std::string categorize(const std::string& fault) {
        if (fault.find("ALTITUDE")    != std::string::npos) return "ALTITUDE";
        if (fault.find("OVERHEAT")    != std::string::npos) return "OVERHEAT";
        if (fault.find("BATTERY")     != std::string::npos) return "BATTERY";
        if (fault.find("GPS")         != std::string::npos) return "GPS";
        return "UNKNOWN";
    }

    std::string mostCriticalSensor() {
        if (faultCount.empty()) return "None";
        return std::max_element(
            faultCount.begin(), faultCount.end(),
            [](const auto& a, const auto& b) { return a.second < b.second; }
        )->first;
    }

    int totalFaults() {
        int total = 0;
        for (auto& p : faultCount) total += p.second;
        return total;
    }

    void printSummary() {
        std::cout << std::endl;
        std::cout << "========================================" << std::endl;
        std::cout << "         FLIGHT FAULT SUMMARY" << std::endl;
        std::cout << "========================================" << std::endl;
        std::cout << "  Total faults detected : " << totalFaults() << std::endl;
        std::cout << "  Most critical sensor  : " << mostCriticalSensor() << std::endl;
        std::cout << std::endl;
        std::cout << "  Fault breakdown:" << std::endl;
        for (auto& p : faultCount) {
            std::cout << "    [" << p.first << "] — " << p.second << " occurrence(s)" << std::endl;
        }
        std::cout << std::endl;
        std::cout << "  Fault timeline:" << std::endl;
        for (auto& p : faultLog) {
            std::cout << "    Tick " << p.first << " → " << p.second << std::endl;
        }
        std::cout << "========================================" << std::endl;
    }
};
