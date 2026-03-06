#pragma once
#include <string>
#include <cstdlib>
#include <cmath>

struct SensorData {
    float altitude;      // meters
    float temperature;   // celsius
    float battery;       // percentage
    bool  gpsSignal;     // true = OK, false = lost

    // Simulate realistic UAV sensor readings with injected faults
    static SensorData simulate(int tick) {
        SensorData data;

        // Normal flight: altitude between 50-120m
        data.altitude = 80.0f + 20.0f * std::sin(tick * 0.3f);

        // Normal temperature: 20-35C
        data.temperature = 27.0f + 3.0f * std::sin(tick * 0.2f);

        // Battery drains over time
        data.battery = 100.0f - (tick * 2.5f);

        // GPS normally fine
        data.gpsSignal = true;

        // --- Inject faults at specific ticks ---

        // Altitude spike at tick 8 (sudden drop)
        if (tick == 8) data.altitude = 12.0f;

        // Overheating at tick 14
        if (tick == 14) data.temperature = 78.0f;

        // Critical battery at tick 20
        if (tick == 20) data.battery = 8.0f;

        // GPS loss at tick 25
        if (tick == 25) data.gpsSignal = false;

        // Double fault: low altitude + GPS loss at tick 28
        if (tick == 28) {
            data.altitude = 6.0f;
            data.gpsSignal = false;
        }

        return data;
    }
};
