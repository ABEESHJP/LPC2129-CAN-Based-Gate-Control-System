# CAN Bus Based Automatic Water-Level Gate Control System

## Overview

The CAN Bus Based Automatic Water-Level Gate Control System is a distributed embedded system developed using three LPC2129 ARM7 microcontroller nodes.

The system automatically senses the water level, communicates the measured value through a CAN bus, displays the corresponding level and status, and controls a gate using a servo motor.

## Objective

To design and implement a distributed embedded system using three LPC2129 microcontroller nodes communicating over a CAN bus to automatically sense the water level, display the corresponding status, and control a gate through a servo motor without manual intervention.

## System Architecture

The system consists of three independent LPC2129 nodes connected through a shared CAN bus.

### Node 1 - Sensing Node

- Uses an MCP3204 12-bit SPI ADC.
- A potentiometer is used as the water-level sensor stand-in.
- Reads the analog input through SPI.
- Transmits the raw ADC value through CAN2.

### Node 2 - Display Node

- Receives the ADC value through CAN.
- Classifies the value into Level 1, Level 2, or Level 3.
- Displays the water-level and gate status on a 16x2 LCD.
- Indicates the current level using three LEDs.

### Node 3 - Actuation Node

- Receives the same CAN data independently.
- Determines the corresponding water-level.
- Controls a servo motor according to the detected level.

## Working Principle

1. The potentiometer provides a variable analog signal representing the water level.
2. MCP3204 converts the analog signal into a 12-bit digital value.
3. Node 1 reads the ADC value through SPI.
4. Node 1 transmits the value through CAN2.
5. Node 2 and Node 3 receive the CAN data independently.
6. Node 2 displays the level and gate status on the LCD and indicates the level using LEDs.
7. Node 3 controls the servo motor according to the detected level.

The ADC produces values from 0 to 4095.

## Level Control

| Level | Status | Servo Position |
|---|---|---|
| Level 1 | Low level / Gate Closed | 0° |
| Level 2 | Medium level | 90° |
| Level 3 | High level / Gate Fully Open | 180° |

## Block Diagram

```text
                 Water-Level Input
                  Potentiometer
                        |
                        v
                +---------------+
                |   MCP3204     |
                |   12-bit ADC  |
                +-------+-------+
                        |
                       SPI
                        |
                        v
                +---------------+
                |    NODE 1     |
                |    LPC2129    |
                | CAN Transmitter|
                +-------+-------+
                        |
                    CAN BUS
                  CAN-H / CAN-L
                   /         \
                  /           \
                 v             v
        +---------------+  +---------------+
        |    NODE 2     |  |    NODE 3     |
        |    LPC2129    |  |    LPC2129    |
        | CAN Receiver  |  | CAN Receiver  |
        +-------+-------+  +-------+-------+
                |                 |
             LCD + LEDs        Servo Motor
                                  |
                                  v
                              Gate Control
Hardware Components
LPC2129 ARM7 Microcontroller - 3 boards
MCP3204 12-bit SPI ADC
Potentiometer
16x2 LCD
LED Indicators - 3
Servo Motor
CAN Transceivers
120Ω CAN termination
Regulated Power Supplies
Software Components
Embedded C
Keil µVision IDE
Flash Magic / ISP Utility
Proteus 8 Professional
SPI
CAN2
PWM
GPIO
Communication
SPI
SPI is used for communication between Node 1 and the MCP3204 ADC.
CAN
CAN is used for communication between the three LPC2129 nodes. Node 1 broadcasts the ADC reading, while Node 2 and Node 3 independently receive and process the same data.
ADC Conversion
MCP3204 is a 12-bit ADC with an output range of 0 to 4095.
For a 3.3 V reference:
Voltage = ADC Value × 3.3 / 4096
Project Features
Automatic water-level monitoring
CAN-based multi-node communication
12-bit ADC measurement
SPI-based ADC interfacing
LCD status display
Three-level LED indication
Servo-based gate control
Distributed embedded architecture
Expandable CAN network
Advantages
Reduces manual intervention.
Provides automatic gate control.
Supports reliable multi-node communication.
Separates sensing, display, and actuation functions.
Easy to extend by adding additional CAN nodes.
Provides real-time level indication.
Applications
Water reservoir management
Irrigation canal gate control
Check dam control
Water storage tank monitoring
Flood-control gate systems
Industrial water-level monitoring
CAN-based distributed automation
Future Scope
Replace the potentiometer with a calibrated ultrasonic or pressure-based water-level sensor.
Add GSM or IoT connectivity for remote monitoring and alerts.
Add data logging for water-level history.
Implement interrupt-driven CAN reception.
Add gate-position feedback for closed-loop control.
Extend the system to control multiple gates using additional CAN nodes.
