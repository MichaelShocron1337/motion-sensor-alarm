# motion-sensor-alarm
IoT motion detection system using ESP32/C++ with HTTP measurements and a Java SOAP-based alarm service.


# IoT Motion Detection & Alarm Service

Individual IoT project developed as part of the **System Integration in IoT** course.

The project consists of an ESP32-based motion detection device written in C++ and a SOAP-based Alarm Service written in Java.

## Overview

A PIR motion sensor connected to an ESP32 detects movement and creates a measurement containing information such as device ID, timestamp, measurement type, value and unit.

The ESP32 connects to Wi-Fi, synchronizes its time using NTP and sends measurements as JSON using HTTP/HTTPS to the system's Integration Service.

The project also includes a Java-based SOAP Alarm Service that follows a predefined WSDL/XSD contract and stores generated alarms in memory.

## Architecture

```text
PIR Motion Sensor
        ↓
      ESP32
       C++
        ↓
Measurement created
        ↓
JSON serialization
        ↓
HTTP / HTTPS
        ↓
Integration Service
```

The individual Alarm Service is implemented separately using Java and SOAP:

```text
Measurement
     ↓
SOAP / XML
     ↓
Java Alarm Service
     ↓
Evaluate Measurement
     ↓
AlarmResult
     ↓
In-memory storage
```

## ESP32

The ESP32 application is written in C++ using the Arduino framework and PlatformIO.

The application is divided into separate components for sensor configuration and network communication.

Main responsibilities include:

- Configure the PIR motion sensor
- Detect motion using GPIO interrupts
- Connect to Wi-Fi
- Synchronize time using NTP
- Create measurement data
- Serialize measurements using JSON
- Send measurements using HTTP/HTTPS
- Identify the device using its MAC address

### Example Measurement

```json
{
  "measurementType": "Motion",
  "measuredAtUtc": "2026-09-23T10:30:00Z",
  "deviceId": "XX:XX:XX:XX:XX:XX",
  "value": 1,
  "unit": "boolean"
}
```

For the PIR sensor, a value of `1` represents detected motion.

## Alarm Service

The Alarm Service is implemented in Java and communicates using SOAP/XML.

The service follows the supplied WSDL/XSD contract.

The contract defines the available operations, request and response structures, data types, element names, namespaces and SOAP faults.

The service provides the following operations:

### EvaluateMeasurement

Receives a measurement and evaluates whether an alarm should be created.

When a measurement triggers an alarm, an `AlarmResult` object is created and stored in memory.

### GetAlarmsByDeviceId

Returns alarms associated with a specific device.

### GetAllAlarms

Returns all alarms currently stored by the Alarm Service.

## Alarm Storage

Created alarms are stored in memory using Java objects.

An alarm contains information such as:

- Device ID
- Measurement information
- Measurement timestamp
- Alarm creation timestamp
- Measurement type
- Value
- Unit
- Alarm message

Because the alarms are stored in RAM, the stored information is temporary and disappears when the Alarm Service is stopped.

## SOAP Communication

The SOAP service uses a predefined WSDL contract.

Conceptually, incoming communication follows this process:

```text
SOAP Request
     ↓
XML
     ↓
SOAP framework
     ↓
Deserialization
     ↓
Java Request Object
     ↓
Application Logic
     ↓
AlarmResult
```

Responses follow the reverse process:

```text
Java Response Object
     ↓
SOAP framework
     ↓
Serialization
     ↓
XML
     ↓
SOAP Response
```

This allows the Java application to work with Java objects while the SOAP framework handles the XML serialization and deserialization.

## Technologies

- C++
- ESP32
- Arduino Framework
- PlatformIO
- PIR Motion Sensor
- GPIO Interrupts
- Wi-Fi
- NTP
- HTTP / HTTPS
- JSON
- ArduinoJson
- Java
- SOAP
- XML
- WSDL
- XSD
- Maven

## Project Structure

```text
project/
│
├── esp32/
│   ├── src/
│   │   ├── main.cpp
│   │   ├── SensorConfig.cpp
│   │   └── ConnectionConfig.cpp
│   │
│   ├── include/
│   │   ├── SensorConfig.h
│   │   └── ConnectionConfig.h
│   │
│   └── platformio.ini
│
├── alarm-service/
│   ├── src/
│   │   └── main/
│   │       ├── java/
│   │       └── resources/
│   │
│   └── pom.xml
│
└── README.md
```

## Purpose

The purpose of the project is to demonstrate system integration between an IoT device and software services using multiple communication technologies.

The project demonstrates concepts including:

- Embedded sensor integration
- Interrupt-driven input
- Network communication
- JSON serialization
- HTTP/HTTPS communication
- REST-based system integration
- SOAP/XML communication
- WSDL contracts
- Java service development
- In-memory data storage
