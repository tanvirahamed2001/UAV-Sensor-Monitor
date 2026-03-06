#include "SensorData.h"
#include "FaultDetector.h"
#include "TelemetryLogger.h"
#include <iostream>
#include <thread>
#include <chrono>

int main() {
    TelemetryLogger logger("telemetry_log.csv");
    FaultDetector detector;

    std::cout << "========================================" << std::endl;
    std::cout << "   UAV Sensor Monitor v1.0" << std::endl;
    std::cout << "   Real-Time Fault Detection System" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << std::endl;

    int tick = 0;
    const int TOTAL_TICKS = 30;

    while (tick < TOTAL_TICKS) {
        // Simulate sensor reading
        SensorData data = SensorData::simulate(tick);

        // Print live telemetry
        std::cout << "[TICK " << tick << "] "
                  << "ALT: " << data.altitude << "m | "
                  << "TEMP: " << data.temperature << "C | "
                  << "BAT: " << data.battery << "% | "
                  << "GPS: " << (data.gpsSignal ? "OK" : "LOST")
                  << std::endl;

        // Run fault detection
        std::string fault = detector.check(data);
        if (!fault.empty()) {
            std::cout << "  *** FAULT DETECTED: " << fault << " ***" << std::endl;
            std::string protocol = detector.triggerFailsafe(fault);
            std::cout << "  >>> FAILSAFE ENGAGED: " << protocol << std::endl;
        }

        // Log to CSV
        logger.log(tick, data, fault);

        tick++;
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }

    std::cout << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "  Mission complete. Log saved to telemetry_log.csv" << std::endl;
    std::cout << "========================================" << std::endl;

    return 0;
}
