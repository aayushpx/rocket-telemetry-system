# Rocket Telemetry System

A high-performance model rocket telemetry suite, featuring real-time sensor fusion, custom C++ drivers, and data visualisation.

## Current Progress
- **Inertial Navigation:**
    - Developed a custom **MPU6050 (Accelerometer/Gyroscope) Class**, using the latest **ESP-IDF v5.2 Master Bus driver**.
    - Successfully implemented the I2C "Who Am I" handshake logic, to verify device communication and bus integrity.
- **Atmospheric & Landing Systems:**
    - Completed a custom DHT11 driver, for environmental monitoring during flight.
    - Developed a Landing Radar Class for the HC-SR04, using microsecond-accurate timing via `esp_timer`.
- **Hardware Engineering:**
    - ESP32-based flight computer prototype established, and ready for flight testing.
    - Implemented a Voltage Divider ($1k\Omega / 2.2k\Omega$), to safely interface 5V sensors with 3.3V logic pins.
    - Integrated an Active Buzzer and LED, for proximity-based alerts during the landing phase.

## Tech Stack
- **Language:** Embedded C++ (using OOP design, for clean sensor abstraction).
- **Framework:** ESP-IDF v5.2 (utilising the new Handle-based I2C API).
- **Hardware:**
    - **ESP32-WROOM** (The main "brain" of the flight computer).
    - **MPU6050** (6-DOF IMU, for tracking orientation and G-forces).
    - **HC-SR04** (Ultrasonic sensor, for the landing radar).
    - **DHT11** (Environmental sensor, for atmospheric data).

## Circuit Logic

### I2C Communication (MPU6050)
The IMU communicates via I2C at 100kHz. **Note:** Proper soldering of the header pins is absolutely essential for signal integrity. Loose connections introduce high resistance, which can cause bit-flipping and garbled data, leading to incorrect device IDs (like seeing `0x70` instead of the expected `0x68`).



### Voltage Divider (Landing Radar)
The HC-SR04 returns a 5V signal, which is too "hot" for the ESP32 logic level. We use a voltage divider to protect the GPIO pins:

$$V_{out} = V_{in} \cdot \frac{R_2}{R_1 + R_2}$$

$$3.43V = 5V \cdot \frac{2200}{1000 + 2200}$$



[Image of a voltage divider circuit diagram]


---

### Maintenance & Debugging
- **I2C Handshake:** Use `idf.py monitor` to check for the `0x68` signature. If the device ID returns `0xFF` or `0x70`, re-check the physical seating of the pins.
- **Data Visualisation:** Plans are in place to stream this data over serial to a Python-based dashboard for real-time graphing.
