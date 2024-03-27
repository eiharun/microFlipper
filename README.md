## Members

Harun Adiyaman, Computer Engineering Student (2025)
haruna@vt.edu

## Mentor

Eddie Pritchard

## Current Status

IN PROGRESS

## Project Overview

> https://docs.flipper.net/development

Microcontroller Implementation of a Flipper Zero device

This project aims to replicate the functionality of the Flipper Zero hacking device using accessible microcontrollers like Arduino, STM32, or ESP32. Inspired by the diverse features of the Flipper Zero, such as WiFi, Sub 1Ghz (Radio), Bluetooth, NFC, RFID, IR, iButton (1-wire), battery capability, MicroSD card for storage, USB-C for CLI (UART)/charging/file transfer, and potentially external GPIO. My implementation will hopefully allow for customization and enhancement beyond the basic Flipper Zero functionality.

### Features

- Wifi
- Sub 1Ghz (Radio)
- Bluetooth
- NFC
- RFID
- IR
- iButton (1-wire)
- Battery Capability
- MicroSD card for Storage
- USB-C for CLI(UART)/Charging/File Transfer
- Perhaps External GPIO

Bonus features:

- Serial Communication Decoder (MITMAtck)

My initial goal is to create a prototype off of a development board with proper documentation such that anyone with the same development board can replicate the project. However my final ambition is to create a custom embedded PCB/handheld device with all the functionality of a flipper zero and hopefully more.

## Educational Value Added

**Embedded C Programming:** Gaining proficiency in programming microcontrollers using embedded C, I'm honing my skills in low-level hardware interaction and optimization.

**Circuit Design:** Through designing circuits tailored to the functionalities of the Flipper Zero device, I'm developing a comprehensive understanding of circuit theory, component selection, and schematic creation.

**Decision-Making Skills:** Crafting a cohesive final product requires making informed decisions regarding hardware selection, software architecture, and feature prioritization, fostering critical thinking and project management skills.

**Embedded Software Engineering:** Delving into the intricacies of embedded software development, I'm learning about task scheduling, memory management, and peripheral interfacing, while adhering to real-time constraints.

**Serial Communication:** Understanding and implementing various serial communication protocols such as UART, SPI, I2C, and CAN are integral to facilitating interaction between the microcontroller and external devices.

**GUI Design:** Incorporating graphical user interfaces (GUIs) enables intuitive user interaction, necessitating proficiency in UI design principles and software frameworks suitable for resource-constrained environments.

**Hardware Interfacing:** Interfacing with diverse hardware modules, sensors, and peripherals necessitates comprehensive knowledge of datasheets, communication protocols, and signal processing techniques.

**Problem Solving:** Encountering and resolving challenges inherent to embedded systems development, including debugging, optimization, and troubleshooting, fosters resilience and adaptive problem-solving skills.

## Tasks

<!-- Your Text Here. You may work with your mentor on this later when they are assigned -->

- Get familiar with new equipment (if any)
- Program LCD GUI and Button Interface
- Program a quick simple game easter egg
- Sub-GHz/Radio
- RFID
- NFC
- IR
- microSD card reader/writer
- GPIO/Module Dev

## Design Decisions

<!-- Your Text Here. You may work with your mentor on this later when they are assigned -->

STM32 Nucleo F747ZI was chosen as the development board for this project due to its high processing power, extensive peripheral support.

128x64 1.3" I2C OLED Display was selected for its compact size, low power consumption, and simplicity of interfacing.

> - May consider a SPI display for faster refresh rates if it becomes an issue

## Design Misc

<!-- Your Text Here. You may work with your mentor on this later when they are assigned -->

## Steps for Documenting Your Design Process

<!-- Your Text Here. You may work with your mentor on this later when they are assigned -->

## BOM + Component Cost

<!-- Your Text Here. You may work with your mentor on this later when they are assigned -->

| Component           | Cost |
| ------------------- | ---- |
| STM32 Nucleo F747ZI | $59  |
| 1.3 OLED Display    | $8   |
| 10 Piece Buttons    | $7   |
| Breadboard          | $9   |
| Breadboard wires    | $12  |

## Timeline

<!-- Your Text Here. You may work with your mentor on this later when they are assigned -->

## Useful Links

<!-- Your Text Here. You may work with your mentor on this later when they are assigned -->

> https://docs.flipper.net/development

> https://hackaday.io/project/170875/logs?sort=oldest

## Log

<!-- Your Text Here. You may work with your mentor on this later when they are assigned -->
