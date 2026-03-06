#pragma once
#include "SensorData.h"
#include <fstream>
#include <string>
#include <iostream>

class TelemetryLogger {
private:
    std::ofstream file;

public:
    TelemetryLogger(const std::string& filename) {
        file.open(filename);
        if (file.is_open()) {
            // Write CSV header
            file << "Tick,Altitude(m),Temperature(C),Battery(%),GPS,Fault,Failsafe\n";
        } else {
            std::cerr << "Warning: Could not open log file." << std::endl;
        }
    }

    ~TelemetryLogger() {
        if (file.is_open()) file.close();
    }

    void log(int tick, const SensorData& data, const std::string& fault) {
        if (!file.is_open()) return;
        file << tick << ","
             << data.altitude << ","
             << data.temperature << ","
             << data.battery << ","
             << (data.gpsSignal ? "OK" : "LOST") << ","
             << (fault.empty() ? "NONE" : fault) << "\n";
        file.flush();
    }
};
