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
========================================
  Mission complete. Log saved to telemetry_log.csv
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
