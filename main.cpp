#include "SensorData.h"
#include "FaultDetector.h"
#include "TelemetryLogger.h"
#include "Config.h"
#include <iostream>
#include <thread>
#include <chrono>

int main() {
    Config config("config.txt");
    FaultDetector detector(config);
    TelemetryLogger logger("telemetry_log.csv");

    std::cout << "========================================" << std::endl;
    std::cout << "   UAV Sensor Monitor v1.1" << std::endl;
    std::cout << "   Real-Time Fault Detection System" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << std::endl;

    for (int tick = 0; tick < config.totalTicks; tick++) {
        SensorData data = SensorData::simulate(tick);

        std::cout << "[TICK " << tick << "] "
                  << "ALT: " << data.altitude << "m | "
                  << "TEMP: " << data.temperature << "C | "
                  << "BAT: " << data.battery << "% | "
                  << "GPS: " << (data.gpsSignal ? "OK" : "LOST")
                  << std::endl;

        std::string fault = detector.check(data);
        if (!fault.empty()) {
            std::cout << "  *** FAULT DETECTED: " << fault << std::endl;
            std::cout << "  >>> FAILSAFE ENGAGED: " << detector.triggerFailsafe(fault) << std::endl;
        }

        logger.log(tick, data, fault);
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }

    std::cout << "\n========================================" << std::endl;
    std::cout << "  Mission complete. Log saved to telemetry_log.csv" << std::endl;
    std::cout << "========================================" << std::endl;

    return 0;
}