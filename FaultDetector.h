#pragma once
#include "SensorData.h"
#include "Config.h"
#include <string>

class FaultDetector {
private:
    float minAltitude;
    float maxTemperature;
    float minBattery;

public:
    FaultDetector(const Config& cfg)
        : minAltitude(cfg.minAltitude),
          maxTemperature(cfg.maxTemperature),
          minBattery(cfg.minBattery) {}

    std::string check(const SensorData& data) {
        if (data.altitude < minAltitude)
            return "CRITICAL ALTITUDE LOW (" + std::to_string((int)data.altitude) + "m)";
        if (data.temperature > maxTemperature)
            return "MOTOR OVERHEAT (" + std::to_string((int)data.temperature) + "C)";
        if (data.battery < minBattery)
            return "CRITICAL BATTERY LOW (" + std::to_string((int)data.battery) + "%)";
        if (!data.gpsSignal)
            return "GPS SIGNAL LOST";
        return "";
    }

    std::string triggerFailsafe(const std::string& fault) {
        if (fault.find("ALTITUDE") != std::string::npos)
            return "EMERGENCY CLIMB INITIATED — ascending to safe altitude";
        if (fault.find("OVERHEAT") != std::string::npos)
            return "THROTTLE REDUCED — cooling protocol engaged";
        if (fault.find("BATTERY") != std::string::npos)
            return "RETURN TO HOME — initiating emergency landing sequence";
        if (fault.find("GPS") != std::string::npos)
            return "HOLDING POSITION — switching to inertial navigation";
        return "GENERAL FAILSAFE — returning to home";
    }
};