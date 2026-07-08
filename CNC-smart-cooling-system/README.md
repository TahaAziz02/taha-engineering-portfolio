# Smart Cooling System for CNC Spindle

**Project Type:** Internship Project  
**Focus Areas:** Embedded Controls, Temperature Monitoring, Pump Control, Fault Detection, Enclosure Design  
**Platform:** Arduino Nano, OneWire Temperature Sensors, TM1637 Display, Relay-Controlled Water Pump  

## Overview

This project involved the design and implementation of a smart water cooling controller for a CNC machine spindle. The system monitored spindle-side temperature and automatically activated an AC water pump when the measured temperature exceeded a user-defined threshold. The controller also provided operator feedback through a 4-digit display and buzzer, while checking for water flow to detect potential pump or coolant circulation issues.

The final system was completed and functional during the internship. This portfolio entry includes the available archived prototype code, pump testing material, a rough concept drawing, and reconstructed documentation based on the final working design.

> **Documentation Note:** This project was completed before I began maintaining a formal engineering portfolio, with all final drafts stored on a company laptop I no longer possess. Original archived documentation is limited to early prototype code, pump testing materials, and rough concept drawings. This page reconstructs the system architecture, design intent, and implementation based on the remaining artifacts and my project experience.

## Project Artifacts

### Prototype Pump Test Setup

![Prototype pump test setup](media/pump-test-setup.jpg)

The pump test setup was used to validate the water circulation portion of the cooling system. The prototype included a AC water pump, tubing, relay-controlled switching hardware, flow sensing, and wiring used during early system testing.

### Early Control Sketch

![Early control sketch](media/rough-control-sketch.jpg)

The early control sketch captured the main embedded interface requirements, including the microcontroller, display output, buzzer drive circuit, analog setpoint input, temperature sensing, and basic input mapping.

## Problem

Small CNC spindles can require active cooling during cutting operations, especially when the spindle is operated for extended periods or under higher thermal load. A manually operated cooling pump creates risk because the operator must remember to activate cooling and monitor the system during use.

The goal of this project was to automate spindle cooling by monitoring temperature, activating water circulation when required, and providing clear user feedback if the cooling loop was not operating correctly.

## System Function

During normal operation, the controller displayed the measured spindle-side temperature. The user could adjust the cooling threshold using a potentiometer and view the setpoint using the pushbutton interface.

When the spindle-side temperature exceeded the selected threshold, the Arduino energized a relay to activate the water pump. The system then checked the flow sensor to confirm that water was circulating. If insufficient flow activity was detected while the pump was expected to be running, the controller displayed a flow error message and triggered the buzzer.

This allowed the CNC spindle cooling system to operate automatically instead of relying on manual pump activation.

## Hardware

| Component | Purpose |
|---|---|
| Arduino Nano | Main embedded controller. |
| OneWire temperature sensors | Measured ambient/reference temperature and spindle-side or pump-side temperature. |
| Potentiometer | Allowed the user to adjust the cooling temperature threshold. |
| Pushbutton | Allowed the user to view or adjust the set temperature. |
| TM1637 4-digit display | Displayed live temperature, setpoint, and error messages. |
| Relay module | Switched the AC water pump on or off. |
| AC water pump | Circulated cooling water through the spindle cooling loop. |
| Flow sensor | Verified coolant flow when the pump was active. |
| Buzzer | Provided audible warning and error feedback. |
| 3D-printed enclosure | Housed the controller electronics for the final system. |

## Software and Control Logic

The firmware was written in Arduino C/C++ and implemented the main control loop for temperature monitoring, setpoint adjustment, pump activation, display output, buzzer warnings, and flow-error detection.

Key software functions included:

- Reading two OneWire temperature sensors
- Mapping potentiometer input to a user-defined temperature threshold
- Applying basic averaging to reduce analog input noise
- Activating a relay-controlled pump when temperature exceeded the threshold
- Sampling the flow sensor to verify water movement
- Displaying live temperature, setpoint, and flow error messages
- Triggering buzzer feedback during cooling and fault conditions

## Outcome

The final system was completed and functional. It automated water pump activation based on CNC spindle temperature and provided operator feedback through a display and buzzer. Through operational observation after implementation, the CNC machine saw an estimated 40% increase in uptime by reducing cooling-related interruptions and the need for manual pump monitoring.

Although the original final build documentation was not preserved, the remaining prototype firmware, pump test hardware, and concept sketches show the core control architecture and implementation path.

## Limitations

Because this project was completed before I began maintaining a formal engineering portfolio, the available documentation is incomplete. The archived materials do not include a polished final schematic, formal test report, or final installed system photos.

## Future Improvements

If revisiting this project, I would improve the documentation and system design by adding a formal wiring schematic, structured test log, cleaned-up firmware revision, sealed enclosure design, and current sensing for additional pump fault detection.
