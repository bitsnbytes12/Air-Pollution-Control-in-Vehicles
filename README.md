# Air Pollution Control in Vehicles

## Overview

Air pollution from vehicle emissions is a major environmental concern, particularly in urban areas. This project presents an Arduino UNO-based embedded system for monitoring harmful gases associated with vehicle emissions.

The system uses **MQ-7, MQ-5, and MQ-135 gas sensors** to monitor changes in gas concentrations. The Arduino UNO processes the sensor outputs and compares them with predefined threshold values. When a pollution level exceeds the specified threshold, the system provides a visual and audible warning.

## Objectives

* Monitor gas pollution associated with vehicle emissions.
* Detect changes in harmful gas concentrations using multiple gas sensors.
* Provide real-time pollution monitoring.
* Alert the user when the measured gas level exceeds the defined threshold.
* Develop a low-cost and simple embedded pollution monitoring system.

## Hardware Components

* Arduino UNO
* MQ-7 Gas Sensor
* MQ-5 Gas Sensor
* MQ-135 Gas Sensor
* 16×2 LCD Display
* Buzzer
* LED
* Resistors
* Jumper Wires
* Breadboard
* 5V Power Supply

## Software

* Arduino IDE
* Embedded C/C++

## Gas Sensors

| Sensor | Primary Detection                         |
| ------ | ----------------------------------------- |
| MQ-7   | Carbon Monoxide (CO)                      |
| MQ-5   | Combustible gases such as LPG and methane |
| MQ-135 | Air-quality-related gases and pollutants  |

The three sensors provide separate analog outputs, allowing the Arduino UNO to monitor each sensor independently.

## Working Principle

The MQ-7, MQ-5, and MQ-135 sensors detect changes in gas concentration and generate corresponding analog output signals.

The Arduino UNO reads these analog signals and processes the sensor values. Each sensor reading is compared with its predefined threshold.

* **Normal Level:** The system displays the measured values and indicates normal conditions.
* **High Pollution Level:** The system activates the buzzer and warning LED and displays the corresponding warning on the LCD.

## System Flow

```text
             Vehicle Emissions
                    |
                    v
       +------------+------------+
       |            |            |
       v            v            v
     MQ-7         MQ-5        MQ-135
       |            |            |
       +------------+------------+
                    |
                    v
              Arduino UNO
                    |
          +---------+---------+
          |         |         |
          v         v         v
        LCD       Buzzer     LED
       Display    Warning   Warning
```

## Circuit Connections

### MQ-7

```text
VCC → Arduino UNO 5V
GND → Arduino UNO GND
AO  → Arduino UNO Analog Pin
```

### MQ-5

```text
VCC → Arduino UNO 5V
GND → Arduino UNO GND
AO  → Arduino UNO Analog Pin
```

### MQ-135

```text
VCC → Arduino UNO 5V
GND → Arduino UNO GND
AO  → Arduino UNO Analog Pin
```

### Warning System

```text
Buzzer → Arduino UNO Digital Pin
LED    → Arduino UNO Digital Pin
LCD    → Arduino UNO Digital Pins
```

## Features

* Real-time gas monitoring
* Three gas sensors for multi-gas detection
* Arduino UNO-based control
* LCD-based display
* Threshold-based warning system
* Audible and visual alerts
* Low-cost embedded implementation

## Future Improvements

* GSM-based SMS alerts
* GPS-based vehicle location tracking
* IoT-based remote monitoring
* Cloud data logging
* Mobile application
* Data analysis and pollution history
* Vehicle emission control mechanism

