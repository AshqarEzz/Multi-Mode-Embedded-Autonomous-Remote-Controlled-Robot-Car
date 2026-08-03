# 🚗 Multi-Mode Embedded Robot Car

Multi-mode embedded robot car featuring autonomous obstacle avoidance, IR remote control, and Bluetooth mobile control. Built with Arduino, ultrasonic sensing, servo scanning, and UART communication — demonstrating real-time control, mode arbitration, and modular embedded system design.

This repository contains multiple versions of the project, developed for an Embedded Systems course. Each version demonstrates a different control method, progressing from basic autonomous behavior to a fully integrated multi-mode system.

> For the full write-up, see `project report.docx`.

---

## 📁 Project Versions

### 1️⃣ Autonomous (`maincar.ino`)
- Ultrasonic-based obstacle avoidance
- Servo scanning for left/right distance measurement
- Automatic path decision without user input
- **Key concepts:** sensor integration, real-time control logic

### 2️⃣ IR Control (`ir-control-car.ino`)
- Manual control using an IR remote (KY-022)
- Directional movement and stop control
- Direct motor actuation via remote commands
- **Key concepts:** IR communication, event-driven input

### 3️⃣ Bluetooth (`bluetooth.ino`)
- Android phone control using HC-06 (ZS-040)
- UART communication via SoftwareSerial
- Character-based command protocol
- **Key concepts:** serial communication, wireless control

### 4️⃣ Autonomous + IR (`IR-REMOTE-MAIN.ino`)
- Default autonomous navigation
- IR remote provides manual override
- Mode switching between auto and manual control
- **Key concepts:** mode switching, control priority

### 5️⃣ All Combined — Final Version (`bluetooth-ir-aut_combined.ino`)
- Autonomous navigation
- IR remote control
- Bluetooth mobile control
- Mode arbitration ensures only one control source drives the motors at a time

**Control priority:** Bluetooth → IR Remote → Autonomous

See `🔘 Mode switching commands.docx` for the exact commands used to switch between modes.

**Key concepts:** system integration, state-based control, modular embedded design

---

## 🛠️ Hardware Used

- Arduino Uno (CH340)
- L298N motor driver
- Ultrasonic sensor
- Servo motor
- IR receiver (KY-022)
- Bluetooth module (HC-06 / ZS-040)

---

## 🎓 Educational Focus

This project demonstrates embedded systems principles including peripheral integration, UART communication, real-time control, and multi-mode system architecture.
