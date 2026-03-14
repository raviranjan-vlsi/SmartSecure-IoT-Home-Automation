# 🏠 SmartSecure: IoT-Based Intelligent Home Automation System

<p align="center">
<img src="Hardware/Complete_System.png" width="600">
</p>

<p align="center">
🚀 Secure • Intelligent • Automated • Connected
</p>

<p align="center">

![Arduino](https://img.shields.io/badge/Platform-Arduino-blue)
![IoT](https://img.shields.io/badge/Technology-IoT-green)
![Embedded](https://img.shields.io/badge/Domain-Embedded%20Systems-orange)
![License](https://img.shields.io/badge/License-MIT-brightgreen)

</p>

---

# 📌 Project Overview

**SmartSecure** is an **IoT-based smart home automation system** designed using **Arduino R4 WiFi**.  
It integrates **security systems, environmental monitoring, automated appliance control, and remote connectivity** to create a safe and intelligent home environment.

The system combines **RFID authentication, environmental sensors, automation logic, and wireless communication** to provide a low-cost and scalable smart home solution.

---

# ✨ Key Features

🔐 **Smart Security**
- RFID based gate authentication  
- Keypad password protection  
- Buzzer alert for unauthorized access  

🌡 **Environmental Monitoring**
- Temperature and humidity monitoring (DHT11)  
- Gas leak detection (MQ-2 sensor)

💡 **Appliance Automation**
- Relay-based control of lights and fan  
- Manual control through touch switches

🌙 **Smart Garden Lighting**
- LDR based automatic light control  
- Energy efficient operation

🌧 **Rain Protection System**
- Rain detection sensor  
- Servo motor based cloth protection

📱 **Remote Connectivity**
- Bluetooth mobile control  
- WiFi IoT dashboard (Blynk)  
- Voice command automation

---

# 🏗 System Architecture

<p align="center">
<img src="Hardware/Block_diagram_of_the_System.png" width="600">
</p>

### Architecture Flow

```
Sensors → Arduino R4 WiFi → Actuators
           ↓
     Bluetooth / WiFi
           ↓
      Mobile App / Blynk
```

---

# 🧠 Working Principle

### 🔐 Gate Control System
RFID cards and keypad passwords authenticate users.  
If credentials are valid, the servo motor opens the gate.

### 🌡 Environmental Monitoring
- **DHT11** monitors temperature and humidity.
- **MQ-2 sensor** detects gas leakage.

### 💡 Appliance Control
Lights and fans are controlled through **relay modules**.

Control methods:
- Touch switch
- Bluetooth mobile app
- IoT dashboard

### 🌙 Garden Light Automation
The **LDR sensor detects ambient light** and automatically turns on garden lights during night.

### 🌧 Clothes Protection
When the **rain sensor detects rainfall**, a servo motor automatically protects clothes from rain.

---

## 🧰 Hardware Components

| Component | Image |
|----------|------|
| Arduino R4 WiFi | <img src="Hardware/arduino_uno_r4_wifi.png" width="120"> |
| Arduino Uno | <img src="Hardware/Arduino_uno.png" width="120"> |
| RFID Module | <img src="Hardware/rfid.png" width="120"> |
| DHT11 Sensor | <img src="Hardware/dht11.png" width="120"> |
| MQ-2 Gas Sensor | <img src="Hardware/mq2.png" width="120"> |
| Rain Sensor | <img src="Hardware/rain_drop.jpg" width="120"> |
| LDR Sensor | <img src="Hardware/ldr.png" width="120"> |
| Servo Motor | <img src="Hardware/servo.png" width="120"> |
| Relay Module | <img src="Hardware/relay.webp" width="120"> |
| LCD Display | <img src="Hardware/lcd.png" width="120"> |


*(Replace these images with photos from your project)*

---

# 💻 Software Tools

| Tool | Purpose |
|----|----|
Arduino IDE | Programming the microcontroller |
Blynk IoT | IoT dashboard and remote monitoring |
MIT App Inventor | Mobile application development |
Embedded C | Firmware development |

---

# 📁 Project Structure

```
SmartSecure-IoT-Home-Automation
│
├── firmware
│   ├── gate_security
│   ├── sensor_monitoring
│   ├── appliance_control
│   └── rain_protection
│
├── hardware
│   ├── circuit_diagram.png
│   └── wiring_connections.png
│
├── docs
│   ├── system_architecture.png
│   ├── block_diagram.png
│   └── project_report.pdf
│
├── images
│   ├── system_overview.jpg
│   ├── prototype.jpg
│   └── components
│
└── README.md
```

---

# 🧪 Testing & Results

### 🔐 Gate Authentication Test

<p align="center">
<img src="images/gate_test.jpg" width="500">
</p>

✔ RFID authentication successful  
✔ Servo gate control working correctly

---

### 🌡 Sensor Monitoring Test

<p align="center">
<img src="images/sensor_test.jpg" width="500">
</p>

✔ Accurate temperature and humidity readings  
✔ Gas detection working properly

---

### 💡 Garden Light Automation

<p align="center">
<img src="images/garden_light_test.jpg" width="500">
</p>

✔ Automatic switching during night  
✔ Energy efficient operation

---

### 🌧 Rain Detection Test

<p align="center">
<img src="images/rain_test.jpg" width="500">
</p>

✔ Rain detection successful  
✔ Servo motor protected clothes automatically

---

# 🎥 Project Demo

📺 Watch the full demo:

```
https://youtube.com/your-demo-video
```

---

# 🚀 Future Improvements

- AI based energy optimization  
- Cloud based data logging  
- Mobile notifications and alerts  
- Integration with smart assistants (Alexa/Google)

---

# 🤝 Contributing

Contributions are welcome!

1. Fork the repository  
2. Create a new feature branch  
3. Commit your changes  
4. Submit a pull request  

---

# 📜 License

This project is released under the **MIT License**.

---

# 👨‍💻 Author

**Raviranjan Kumar**

🎓 B.Tech - Electronics and Communication Engineering  
🎓 M.Tech - Embedded System Design 
💡 Embedded Systems | IoT | VLSI Enthusiast
