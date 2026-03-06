#pragma once
#include "SensorData.h"
#include <string>

class FaultDetector {
public:
    // Fault thresholds
    const float MIN_ALTITUDE    = 15.0f;   // meters
    const float MAX_TEMPERATURE = 70.0f;   // celsius
    const float MIN_BATTERY     = 10.0f;   // percent

    // Check all sensors and return fault description, empty string if all OK
    std::string check(const SensorData& data) {
        if (data.altitude < MIN_ALTITUDE) {
            return "CRITICAL ALTITUDE LOW (" + std::to_string((int)data.altitude) + "m)";
        }
        if (data.temperature > MAX_TEMPERATURE) {
            return "MOTOR OVERHEAT (" + std::to_string((int)data.temperature) + "C)";
        }
        if (data.battery < MIN_BATTERY) {
            return "CRITICAL BATTERY LOW (" + std::to_string((int)data.battery) + "%)";
        }
        if (!data.gpsSignal) {
            return "GPS SIGNAL LOST";
        }
        return "";
    }

    // Trigger appropriate failsafe protocol based on fault type
    std::string triggerFailsafe(const std::string& fault) {
        if (fault.find("ALTITUDE") != std::string::npos) {
            return "EMERGENCY CLIMB INITIATED — ascending to safe altitude";
        }
        if (fault.find("OVERHEAT") != std::string::npos) {
            return "THROTTLE REDUCED — cooling protocol engaged";
        }
        if (fault.find("BATTERY") != std::string::npos) {
            return "RETURN TO HOME — initiating emergency landing sequence";
        }
        if (fault.find("GPS") != std::string::npos) {
            return "HOLDING POSITION — switching to inertial navigation";
        }
        return "GENERAL FAILSAFE — returning to home";
    }
};
