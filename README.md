# GreenHouse IoT System

This repository contains the source code for a simple **IoT greenhouse prototype** using an ESP32 microcontroller and sensors for educational purposes. The system measures soil moisture, ambient temperature and humidity, and water level in the irrigation reservoir. It demonstrates basic sensor integration and control logic.

---

## Features

- Reads **soil moisture** with a capacitive sensor.
- Measures **temperature and humidity** using the AHT10 sensor.
- Monitors **water level** in a tank using an ultrasonic sensor.
- Implements basic logic to trigger actions based on sensor readings.
- Demonstrates ESP32 programming and sensor interfacing for learning purposes.

---

## Hardware Components

- ESP32 microcontroller
- Capacitive Soil Moisture Sensor
- AHT10 Temperature and Humidity Sensor
- HC-SR04 Ultrasonic Sensor
- Breadboard, jumper wires, and other basic components

---

## Software

- Arduino IDE
- Adafruit AHTX0 library
- Wire library for I2C communication

---

## Wiring

- **Soil Moisture Sensor:** Analog input to pin `34`
- **Ultrasonic Sensor:**  
  - TRIG → pin `33`  
  - ECHO → pin `35`  
- **AHT10 Sensor:** I2C pins `21` (SDA) and `22` (SCL)
