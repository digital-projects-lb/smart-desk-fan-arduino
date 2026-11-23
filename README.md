# Proximity & Thermal Smart Desk Fan (Arduino + Linux CLI)

An automated embedded cooling system built on **Arduino Uno** and deployed via **Arduino CLI** on Linux/Windows. The system monitors ambient temperature and desk occupancy in real time—activating a dual-servo cooling fan only when temperatures exceed **30°C** and a user is detected within **20 cm**.

🎥 **Hardware Demo Video:** [Watch on YouTube](https://youtu.be)

---

## Key Features & System Logic
* **Occupancy Detection (HC-SR04 Ultrasonic + Servo Sweeper):** Continuously scans the desk area and measures user proximity in centimeters.
* **Thermal Status Feedback (RGB LED):**
  * 🔵 **Blue (`< 10°C`):** Cold ambient state
  * 🟢 **Green (`10°C – 30°C`):** Optimal comfort range
  * 🔴 **Red (`> 30°C`):** High-temperature alert
* **Automated Actuation (Servo Fan):** Engages cooling oscillation only when **Temperature > 30°C** AND **Proximity < 20 cm**.
* **Headless CLI Deployment:** Compiled, flashed, and monitored via serial interface using `arduino-cli` without relying on a GUI IDE.

---

## Hardware Architecture

| Component | Arduino Pin | Function |
| :--- | :--- | :--- |
| **DHT11 Sensor** | `D4` | Digital temperature & humidity input |
| **HC-SR04 Ultrasonic** | `D7` (TRIG), `D6` (ECHO) | Desk occupancy distance measurement |
| **RGB LED (with 1kΩ resistors)** | `D10` (R), `D9` (G), `D8` (B) | Visual thermal state indicator |
| **Fan Servo (`servo1`)** | `D2` | Automated cooling fan actuation |
| **Scanner Servo (`servo2`)** | `D3` | 180° ultrasonic sensor rotation |

---

## Quick Start (Arduino CLI)

```bash
# 1. Install board core & libraries
arduino-cli core update-index
arduino-cli core install arduino:avr
arduino-cli lib install "DHT11" "Servo"

# 2. Compile & upload to Arduino Uno
cd FAN
arduino-cli compile -b arduino:avr:uno -u -p COM4

# 3. View live telemetry (9600 baud)
arduino-cli monitor -p COM4 -c baudrate=9600
```

---

## Future Roadmap
* **Non-blocking `millis()` scheduler** to decouple ultrasonic sweep timing from fan actuation.
* **Wireless telemetry & mobile control** via Bluetooth (HC-05) or ESP32 Wi-Fi migration.
* **Data logging** to microSD for long-term desk thermal analytics.
