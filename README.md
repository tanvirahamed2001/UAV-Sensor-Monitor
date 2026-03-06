<div align="center">

# 🚁 UAV Sensor Monitor & Fault Detection System

**A real-time C++ telemetry processing pipeline with automated fault detection and failsafe protocol triggering.**

[![Language](https://img.shields.io/badge/C%2B%2B-11-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)](https://isocpp.org/)
[![Platform](https://img.shields.io/badge/Platform-macOS%20%7C%20Linux-lightgrey?style=for-the-badge&logo=linux&logoColor=white)](https://github.com/tanvirahamed2001/UAV-Sensor-Monitor)
[![Domain](https://img.shields.io/badge/Domain-UAV%20Systems-orange?style=for-the-badge&logo=drone&logoColor=white)](https://github.com/tanvirahamed2001/UAV-Sensor-Monitor)
[![Status](https://img.shields.io/badge/Status-Complete-brightgreen?style=for-the-badge)](https://github.com/tanvirahamed2001/UAV-Sensor-Monitor)

</div>

---

## 📡 Overview

This project simulates the core sensor monitoring loop found in UAV flight control systems. It continuously reads telemetry data from onboard sensors, evaluates readings against configurable safety thresholds, and triggers appropriate failsafe responses when anomalies are detected — all while logging every event to a CSV file for post-flight analysis.

---

## ⚡ Features

| Feature | Description |
|--------|-------------|
| 📊 **Real-time sensor simulation** | Streams altitude, temperature, battery, and GPS data tick-by-tick |
| 🔍 **Fault detection engine** | Threshold-based anomaly detection across all sensor channels |
| 🛡️ **Automated failsafe protocols** | Context-aware responses triggered per fault type |
| 🧵 **Multi-threaded architecture** | Sensor producer and fault detector run on separate threads with mutex-protected shared queue |
| 📁 **Telemetry logging** | All sensor readings and fault events written to `telemetry_log.csv` |
| 📈 **Fault history & statistics** | Tracks fault frequency, timeline, and most critical sensor across the session |
| ⚙️ **Runtime configuration** | Thresholds loaded from `config.txt` at startup — no recompile needed |
| 💥 **Injected fault scenarios** | Simulates altitude drop, motor overheat, battery critical, GPS loss, and compound faults |

---

## 🚨 Fault Scenarios

| Fault | Threshold | Failsafe Response |
|-------|-----------|-------------------|
| 🔴 Altitude too low | < 15m | Emergency climb initiated |
| 🌡️ Motor overheat | > 70°C | Throttle reduced, cooling engaged |
| 🔋 Battery critical | < 10% | Return to home, emergency landing |
| 📡 GPS signal lost | N/A | Hold position, switch to inertial nav |

---

## 🗂️ Project Structure

```
UAV-Sensor-Monitor/
├── main.cpp            # Entry point — launches producer/consumer threads
├── SensorData.h        # Sensor data model + tick-based simulation
├── FaultDetector.h     # Fault detection engine + failsafe logic
├── TelemetryLogger.h   # CSV telemetry logger
├── FaultStats.h        # Fault history, frequency tracking, session summary
├── Config.h            # Runtime config loader from config.txt
└── config.txt          # Configurable thresholds (edit without recompiling)
```

---

## 🛠️ Tech Stack

<div align="center">

![C++](https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![VS Code](https://img.shields.io/badge/VS%20Code-007ACC?style=for-the-badge&logo=visual-studio-code&logoColor=white)
![Git](https://img.shields.io/badge/Git-F05032?style=for-the-badge&logo=git&logoColor=white)
![GitHub](https://img.shields.io/badge/GitHub-181717?style=for-the-badge&logo=github&logoColor=white)

</div>

**Concepts:** Real-time data processing · Fault detection · Failsafe systems · Telemetry logging · OOP · Embedded systems simulation

---

## 🚀 Build & Run

```bash
# Compile (pthread required for multithreading)
g++ -std=c++11 main.cpp -o uav_monitor -pthread

# Run
./uav_monitor
```

---

## 🖥️ Sample Output

```
[CONFIG] Loaded thresholds from config.txt
  MIN_ALTITUDE    = 15m
  MAX_TEMPERATURE = 70C
  MIN_BATTERY     = 10%
  TOTAL_TICKS     = 30

========================================
   UAV Sensor Monitor v2.0
   Real-Time Fault Detection System
========================================

[TICK  0] ALT:    80.0m | TEMP:  27.0C | BAT: 100.0% | GPS: OK
[TICK  1] ALT:    85.9m | TEMP:  27.6C | BAT:  97.5% | GPS: OK
...
[TICK  8] ALT:    12.0m | TEMP:  30.0C | BAT:  80.0% | GPS: OK
  *** FAULT    : CRITICAL ALTITUDE LOW (12m)
  >>> FAILSAFE : EMERGENCY CLIMB INITIATED — ascending to safe altitude
[TICK 14] ALT:    62.6m | TEMP:  78.0C | BAT:  65.0% | GPS: OK
  *** FAULT    : MOTOR OVERHEAT (78C)
  >>> FAILSAFE : THROTTLE REDUCED — cooling protocol engaged
[TICK 20] ALT:    74.4m | TEMP:  24.7C | BAT:   8.0% | GPS: OK
  *** FAULT    : CRITICAL BATTERY LOW (8%)
  >>> FAILSAFE : RETURN TO HOME — initiating emergency landing sequence
[TICK 25] ALT:    98.8m | TEMP:  24.1C | BAT:  37.5% | GPS: LOST
  *** FAULT    : GPS SIGNAL LOST
  >>> FAILSAFE : HOLDING POSITION — switching to inertial navigation
[TICK 28] ALT:     6.0m | TEMP:  25.1C | BAT:  30.0% | GPS: LOST
  *** FAULT    : CRITICAL ALTITUDE LOW (6m)
  >>> FAILSAFE : EMERGENCY CLIMB INITIATED — ascending to safe altitude

  Mission complete. Log saved to telemetry_log.csv

========================================
         FLIGHT FAULT SUMMARY
========================================
  Total faults detected : 5
  Most critical sensor  : ALTITUDE

  Fault breakdown:
    [ALTITUDE] — 2 occurrence(s)
    [BATTERY]  — 1 occurrence(s)
    [GPS]      — 1 occurrence(s)
    [OVERHEAT] — 1 occurrence(s)

  Fault timeline:
    Tick  8 → CRITICAL ALTITUDE LOW (12m)
    Tick 14 → MOTOR OVERHEAT (78C)
    Tick 20 → CRITICAL BATTERY LOW (8%)
    Tick 25 → GPS SIGNAL LOST
    Tick 28 → CRITICAL ALTITUDE LOW (6m)
========================================
```

---

## 👤 Author

<div align="center">

**Tanvir Ahamed Himel**
Bachelor of Science, Computer Science — University of Calgary

[![LinkedIn](https://img.shields.io/badge/LinkedIn-0A66C2?style=for-the-badge&logo=linkedin&logoColor=white)](https://www.linkedin.com/in/tanvir-ahamed-himel-1b96a0260/)
[![GitHub](https://img.shields.io/badge/GitHub-181717?style=for-the-badge&logo=github&logoColor=white)](https://github.com/tanvirahamed2001)

</div>
