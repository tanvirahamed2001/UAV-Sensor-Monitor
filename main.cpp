#include "SensorData.h"
#include "FaultDetector.h"
#include "TelemetryLogger.h"
#include "FaultStats.h"
#include "Config.h"
#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <atomic>
#include <chrono>
#include <iomanip>

// -------------------------------------------------------
// Shared state between sensor thread and detector thread
// -------------------------------------------------------
std::queue<std::pair<int, SensorData>> sensorQueue; // {tick, data}
std::mutex queueMutex;
std::atomic<bool> missionComplete(false);

// -------------------------------------------------------
// THREAD 1: Sensor Producer
// Simulates reading from onboard sensors and pushes
// readings into the shared queue at a fixed interval.
// -------------------------------------------------------
void sensorProducer(int totalTicks) {
    for (int tick = 0; tick < totalTicks; tick++) {
        SensorData data = SensorData::simulate(tick);
        {
            std::lock_guard<std::mutex> lock(queueMutex);
            sensorQueue.push({tick, data});
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
    missionComplete = true;
}

// -------------------------------------------------------
// THREAD 2: Fault Detector Consumer
// Reads sensor readings from the shared queue, runs
// fault detection, logs events, and updates stats.
// -------------------------------------------------------
void faultDetectorConsumer(FaultDetector& detector,
                           TelemetryLogger& logger,
                           FaultStats& stats) {
    while (!missionComplete || !sensorQueue.empty()) {
        std::pair<int, SensorData> entry;
        bool hasData = false;

        {
            std::lock_guard<std::mutex> lock(queueMutex);
            if (!sensorQueue.empty()) {
                entry = sensorQueue.front();
                sensorQueue.pop();
                hasData = true;
            }
        }

        if (!hasData) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            continue;
        }

        int tick           = entry.first;
        SensorData data    = entry.second;

        // Print live telemetry
        std::cout << "[TICK " << std::setw(2) << tick << "] "
                  << "ALT: "  << std::setw(7) << std::fixed << std::setprecision(1) << data.altitude  << "m | "
                  << "TEMP: " << std::setw(5) << std::fixed << std::setprecision(1) << data.temperature << "C | "
                  << "BAT: "  << std::setw(5) << std::fixed << std::setprecision(1) << data.battery    << "% | "
                  << "GPS: "  << (data.gpsSignal ? "OK  " : "LOST")
                  << std::endl;

        // Run fault detection
        std::string fault = detector.check(data);
        if (!fault.empty()) {
            std::string protocol = detector.triggerFailsafe(fault);
            std::cout << "  *** FAULT    : " << fault    << std::endl;
            std::cout << "  >>> FAILSAFE : " << protocol << std::endl;
            stats.record(tick, fault);
        }

        // Log to CSV
        logger.log(tick, data, fault);
    }
}

// -------------------------------------------------------
// MAIN
// -------------------------------------------------------
int main() {
    // Load config from file (falls back to defaults if missing)
    Config config("config.txt");

    FaultDetector  detector(config);
    TelemetryLogger logger("telemetry_log.csv");
    FaultStats     stats;

    std::cout << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "   UAV Sensor Monitor v2.0              " << std::endl;
    std::cout << "   Real-Time Fault Detection System     " << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << std::endl;

    // Launch sensor producer and fault detector on separate threads
    std::thread producer(sensorProducer, config.totalTicks);
    std::thread consumer(faultDetectorConsumer,
                         std::ref(detector),
                         std::ref(logger),
                         std::ref(stats));

    // Wait for both threads to finish
    producer.join();
    consumer.join();

    std::cout << std::endl;
    std::cout << "  Mission complete. Log saved to telemetry_log.csv" << std::endl;

    // Print end-of-flight fault summary
    stats.printSummary();

    return 0;
}
