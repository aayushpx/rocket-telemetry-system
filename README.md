# Rocket Telemetry System

A high-performance model rocket telemetry suite featuring real-time sensor fusion, C++ drivers, and data visualization.

## Current Progress
- **Firmware:** - Completed custom DHT11 driver.
    - Developed Landing Radar Class for HC-SR04 using microsecond-accurate timing via `esp_timer`.
- **Hardware:** - ESP32-based flight computer prototype established.
    - Implemented a Voltage Divider (1kΩ/2.2kΩ) to interface 5V sensors with 3.3V logic.
    - Integrated Active Buzzer and LED for proximity-based landing alerts.

## Tech Stack
- **Language:** Embedded C++
- **Framework:** ESP-IDF v5.2
- **Hardware:** - ESP32-WROOM
    - HC-SR04 Ultrasonic Sensor
    - DHT11 Environmental Sensor
    - Active Buzzer & Status LEDs

## Circuit Logic
The landing radar utilizes an ultrasonic pulse-echo sequence. Because the HC-SR04 returns a 5V signal, a voltage divider is used on the Echo line to protect the ESP32:
- $V_{out} = V_{in} \cdot \frac{R_2}{R_1 + R_2}$
- $3.43V = 5V \cdot \frac{2200}{1000 + 2200}$
