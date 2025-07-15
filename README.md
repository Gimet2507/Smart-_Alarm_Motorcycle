# 🚨 Smart Alarm Motorcycle (IoT GPS Tracker & Anti-Theft Alert)

This project is an **IoT-based motorcycle security system** that utilizes an **ESP8266**, **GPS module**, **vibration sensor**, and **relay**, while integrating with the **Blynk App** and **Telegram Bot**. It can detect vibrations, trigger an alarm, and send **real-time GPS location** updates directly to the user's smartphone.

---

## 📌 Features

- Detects vibration or suspicious activity
- Sends real-time **GPS coordinates** via Telegram
- Includes clickable **Google Maps link**
- Activates **relay module** for alarms or engine lock
- Sends live status to **Blynk App**
- Remote monitoring and control over Wi-Fi

---

## 🧠 Technology Used

### Hardware

- ESP8266 NodeMCU
- GPS Module (e.g., NEO-6M)
- Vibration Sensor Module
- Relay Module
- Buzzer/Siren (optional)
- Jumper wires, breadboard

### Software

- Arduino IDE
- Blynk IoT Platform
- TinyGPS++ library
- UniversalTelegramBot library
- Telegram Bot API

---

## ⚙️ How It Works

1. The vibration sensor continuously monitors for unusual movement.
2. If a vibration is detected, the **relay module** is triggered to activate an alarm.
3. At the same time, GPS data is obtained and a **Telegram message** is sent with coordinates.
4. The message includes a clickable **Google Maps link** for tracking.
5. The Blynk app receives live updates through virtual pins.

---

## 🔌 Wiring Diagram

| Component         | ESP8266 Pin |
|------------------|-------------|
| GPS RX (TX pin)  | D1 (GPIO5)  |
| GPS TX (RX pin)  | D2 (GPIO4)  |
| Vibration Sensor | D3 (GPIO0)  |
| Relay IN         | D6 (GPIO12) |

> Make sure to connect GPS module power pins properly (usually 3.3V or 5V depending on the module). GPS communication uses **SoftwareSerial**.

---

## 📲 Blynk Virtual Pins

| Function             | Virtual Pin |
|----------------------|-------------|
| Vibration Status     | V0          |
| Relay State (ON/OFF) | V1          |

---

## 🛠️ Required Hardware

- 1x NodeMCU ESP8266
- 1x GPS Module (NEO-6M recommended)
- 1x Vibration Sensor Module
- 1x Relay Module
- 1x Siren or Buzzer (optional)
- Breadboard, Jumper Wires, USB Cable

---

## 🛡️ Security Tips

- ⚠️ **Never share your Wi-Fi credentials**, Blynk Auth Token, or Telegram Bot Token publicly.
- Use `.env` files or secure credential storage methods for real deployment.

---

Let me know if you want a visual schematic, GitHub README file, or Instructables-style tutorial.
