# Formula SAE EV Battery Monitoring Board

## Overview

Contributed to the design and development of a battery temperature monitoring system for the University of Alberta Formula SAE Electric Vehicle team. The project focused on designing a reliable thermistor interface board for the Orion Battery Management System (BMS), enabling accurate temperature monitoring of pouch-cell battery modules while meeting Formula SAE EV safety requirements.

---

## Problem

Formula SAE Electric vehicles require continuous battery temperature monitoring to ensure safe operation and compliance with competition regulations. The monitoring system needed to provide reliable sensor connectivity, simplify assembly and servicing, and integrate directly with the Orion BMS.

---

## My Contributions

My responsibilities included:

- Schematic capture in KiCad
- PCB layout and routing
- Thermistor placement planning
- Connector selection
- Orion BMS integration
- Design reviews
- Rule compliance verification
- Collaboration with mechanical and controls teams

---

## Hardware

- Orion Battery Management System (BMS)
- NTC Thermistors
- Custom KiCad PCB
- JST Connectors
- Samtec Board Connectors

---

## Design Considerations

The PCB was designed with emphasis on:

- Accurate temperature sensing
- Reliable electrical connections
- Ease of manufacturing
- Ease of serviceability
- Electrical isolation
- Battery module packaging constraints
- Formula SAE EV rule compliance

---

## Engineering Challenges

### Thermistor Interface Architecture

Previous accumulator designs used thermistors connected in series due to the battery modules utilizing thermal diodes rather than true NTC thermistors. The redesigned system instead routes each thermistor independently to the connector, allowing every sensor to be monitored individually by the BMS.

This architecture required routing 54 dedicated thermistor signal lines while maintaining a compact PCB footprint and organized connector layout.

---

### Redundant Voltage Measurement

The accumulator was designed to support redundant voltage sensing for each battery cell.

Each cell includes three independent voltage taps with separate fusing to provide fault tolerance for the battery management system. This architecture allows the system to continue operating even if individual voltage taps or fuses fail.

Connector placement was optimized so that each cell tap was located adjacent to its corresponding busbar, reducing wiring complexity while simplifying assembly and maintenance.

---

### Mechanical Integration

The PCB had to fit completely within the battery module while avoiding interference with:

- Cell compression hardware
- Busbars
- High-voltage connections
- Battery tabs
- Service access

Connector locations were selected to minimize harness length while maintaining accessibility during assembly and maintenance.

---

### Electrical Safety

The board was designed to interface directly with the Orion BMS using electrically isolated 10kΩ NTC thermistors with a common β value of 3380 K.

**Maintaining identical thermistor characteristics and proper electrical isolation was essential for accurate temperature monitoring and safe operation.**


---

## Skills Demonstrated

- PCB Design
- KiCad
- Schematic Capture
- PCB Layout
- Battery Management Systems
- Sensor Integration
- Design Reviews
- Engineering Documentation
- Cross-Disciplinary Collaboration

---

## Outcome

Contributed to the successful development of a battery temperature monitoring solution that supported safe battery operation and integration with the vehicle's Orion BMS. The project strengthened practical experience in PCB design, battery systems, and engineering collaboration within a multidisciplinary motorsports team.

---

## Photos

### PCB Layout

### Schematic

### Battery Module Integration

### Formula SAE Vehicle
