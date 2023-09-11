# Mini Automation: MQTT-Based PLC Software for ESP32

Welcome to the Mini Automation project repository! Mini Automation is an open-source MQTT-based Programmable Logic Controller (PLC) software designed to run on ESP32 microcontrollers. This project aims to provide a robust foundation for building versatile control applications, focusing on home automation as its initial use case.

## Project Overview

### Purpose

Mini Automation is developed to create a foundation for building IoT control systems that utilize MQTT for seamless communication between devices. The software architecture is built with flexibility and extensibility in mind, making it easy for developers to create various control tasks.

### Key Features (WIP)

- **Multi-Core Support:** The software efficiently utilizes the ESP32's dual-core architecture, running two tasks on Core 1. One task is responsible for displaying a mini GUI on an OLED display, while the other manages the execution of control tasks. Core 0 handles network connection and MQTT communication processing.

- **Intuitive API:** We aim to provide a developer-friendly API that simplifies the creation of control tasks for various applications.

- **Bidirectional MQTT Communication:** Mini Automation facilitates the exchange of data via MQTT, allowing devices to both publish and subscribe to MQTT topics with defined data entities.

- **Customizable User Interface:** A basic user interface is provided on the device via a customizable menu system. Developers can extend this interface to meet specific requirements.

- **EEPROM Storage:** Mini Automation includes functionality to store user settings and critical information in the ESP32's EEPROM, ensuring data persistence across power cycles.

- **OTA (Over-The-Air) Updates:** Basic OTA functionality is supported, making it convenient to update the software remotely.

## Use Case: Home Automation

The initial use case for Mini Automation focuses on home automation. Specifically, it aims to enable control of a heating system, using MQTT and integration with platforms like Home Assistant. This use case serves as a practical example of how Mini Automation can be applied in real-world scenarios.
