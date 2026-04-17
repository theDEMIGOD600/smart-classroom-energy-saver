# 📘 IoT-Based Smart Classroom Environment Monitoring System

## 📌 Overview

The IoT-Based Smart Classroom Environment Monitoring System is designed to monitor classroom conditions in real time and improve energy efficiency automatically.

This system uses an ESP32 microcontroller along with multiple sensors to track:

- Temperature 🌡️
- Humidity 💧
- Light intensity 💡
- Occupancy 👨‍🎓

Based on sensor data, the system intelligently controls lighting and simulates AC settings while displaying all information on an OLED screen.

---

## 🚀 Features

- 👥 People Counting System using IR sensors (Entry & Exit)
- 🌡️ Temperature & Humidity Monitoring (DHT11)
- 💡 Automatic Light Control using LDR sensor
- ❄️ AC Simulation based on temperature
- 💤 Idle Mode when no occupants are present (energy saving)
- 📟 Real-time Display on OLED screen

---

## 🛠️ Components Used

- ESP32 Microcontroller
- Breadboard
- OLED Display (SSD1306)
- DHT11 Sensor
- IR Sensors (2 – Entry & Exit)
- LDR Module
- LEDs (4)
- Resistors
- Jumper Wires
- Power Supply

---

## 🔌 Circuit Connections

| Component | ESP32 Pin                      |
| --------- | ------------------------------ |
| OLED SDA  | GPIO21                         |
| OLED SCL  | GPIO22                         |
| DHT11     | GPIO4                          |
| IR Entry  | GPIO13                         |
| IR Exit   | GPIO14                         |
| LDR       | GPIO34 (Analog)                |
| LEDs      | GPIO25, GPIO26, GPIO27, GPIO32 |

---

## ⚙️ Working Principle

1. System initializes all sensors and displays a welcome message.
2. IR sensors track people entering and exiting → maintain count.
3. DHT11 reads temperature & humidity.
4. LDR detects ambient light.
5. Based on inputs:
   - Adjust LED brightness
   - Simulate AC temperature
6. If no people detected:
   - System enters IDLE mode
   - LEDs turn OFF
7. All data is continuously displayed on OLED.

---

## 🧠 Pseudocode

```
START
Initialize components
Set peopleCount = 0

LOOP:
  IF entry detected → peopleCount++
  IF exit detected → peopleCount--

  Read temperature
  Read light intensity

  Adjust AC setting
  Adjust LEDs

  IF peopleCount == 0:
    Turn OFF LEDs
    Display IDLE
  ELSE:
    Display ACTIVE

  Update OLED
END LOOP
```

---

## 🎯 Applications

- Smart Classrooms
- Energy-efficient buildings
- Offices & meeting rooms
- IoT-based automation systems

---

## 📈 Advantages

- Reduces energy consumption
- Fully automated system
- Real-time monitoring
- Cost-effective and scalable

---

## 🔮 Future Improvements

- Integration with mobile app
- Real AC control instead of simulation
- Cloud data storage
- AI-based occupancy prediction

---

## 👨‍💻 Team Members

- Uthkarsha
- Varun M L
- Dhruvanth U

---

## 📄 Project Report

Refer to the project PDF for detailed explanation.
