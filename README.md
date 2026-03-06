# UAV Sensor Monitor & Fault Detection System

A C++ simulation of a real-time UAV telemetry processing pipeline with automated fault detection and failsafe protocol triggering.

## Overview

This project simulates the core sensor monitoring loop found in UAV flight control systems. It continuously reads telemetry data from onboard sensors, evaluates readings against configurable safety thresholds, and triggers appropriate failsafe responses when anomalies are detected — all while logging every event to a CSV file for post-flight analysis.

## Features

- **Real-time sensor stream simulation** — altitude, temperature, battery, GPS
- **Configurable fault detection** — threshold-based anomaly detection across all sensor channels
- **Automated failsafe protocols** — context-aware responses per fault type
- **Telemetry logging** — all sensor readings and fault events written to `telemetry_log.csv`
- **Injected fault scenarios** — simulates altitude drop, motor overheat, battery critical, GPS loss, and compound faults

## Fault Scenarios

| Fault | Threshold | Failsafe Response |
|-------|-----------|-------------------|
| Altitude too low | < 15m | Emergency climb initiated |
| Motor overheat | > 70°C | Throttle reduced, cooling engaged |
| Battery critical | < 10% | Return to home, emergency landing |
| GPS signal lost | N/A | Hold position, switch to inertial nav |

## Project Structure

```
UAV-Sensor-Monitor/
├── main.cpp            # Entry point — monitoring loop
├── SensorData.h        # Sensor data model + simulation
├── FaultDetector.h     # Fault detection engine + failsafe logic
├── TelemetryLogger.h   # CSV telemetry logger
└── telemetry_log.csv   # Generated on run
```

## Build & Run

```bash
# Compile
g++ -std=c++11 main.cpp -o uav_monitor

# Run
./uav_monitor
```

## Sample Output

```
========================================
   UAV Sensor Monitor v1.0
   Real-Time Fault Detection System
========================================

[TICK 0]  ALT: 80m  | TEMP: 27C | BAT: 100% | GPS: OK
[TICK 8]  ALT: 12m  | TEMP: 25C | BAT: 80%  | GPS: OK
  *** FAULT DETECTED: CRITICAL ALTITUDE LOW (12m) ***
  >>> FAILSAFE ENGAGED: EMERGENCY CLIMB INITIATED — ascending to safe altitude
[TICK 14] ALT: 90m  | TEMP: 78C | BAT: 65%  | GPS: OK
  *** FAULT DETECTED: MOTOR OVERHEAT (78C) ***
  >>> FAILSAFE ENGAGED: THROTTLE REDUCED — cooling protocol engaged
[TICK 20] ALT: 85m  | TEMP: 28C | BAT: 8%   | GPS: OK
  *** FAULT DETECTED: CRITICAL BATTERY LOW (8%) ***
  >>> FAILSAFE ENGAGED: RETURN TO HOME — initiating emergency landing sequence
[TICK 25] ALT: 72m  | TEMP: 26C | BAT: 37%  | GPS: LOST
  *** FAULT DETECTED: GPS SIGNAL LOST ***
  >>> FAILSAFE ENGAGED: HOLDING POSITION — switching to inertial navigation
```

## Tech Stack

- **Language:** C++11
- **Concepts:** Real-time data processing, fault detection, failsafe systems, telemetry logging, OOP

## Author

Tanvir Ahamed Himel — University of Calgary, Computer Science
