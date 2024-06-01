# Current Meter Arduino Project

## Overview
This project is designed for an operating systems course and involves using an Arduino to measure electrical current. The measured data is saved and can be accessed from a Linux system, where it can be plotted for analysis.

## Project Structure

The project is organized into two main directories: `arduino` and `linux`.


## Arduino Directory

The `arduino` directory contains all the files necessary for running the current measurement on the Arduino. The key files include:

- **adc.c / adc.h**: Code for the Analog-to-Digital Converter.
- **arduino.c**: Main file for Arduino operations.
- **compile.sh**: Script to compile and flash the Arduino code (Atmega 328p).
- **Makefile**: Makefile to facilitate the build process.
- **uart.c / uart.h**: Code for UART communication.
- **timers.c / timers.h**: Timers initialization.
- **utils.c / utils.h**: Utility functions.

Additionally, the `avr_common` subdirectory contains:

- **avr.mk**: Makefile for AVR-specific settings.

## Linux Directory

The `linux` directory contains the files needed to compile, run, and plot data on a Linux system. Key files include:

- **compile.sh**: Script to compile the Linux code.
- **main.c**: Main file for Linux-side operations.
- **Makefile**: Makefile to facilitate the build process.
- **plot.sh**: Script to plot the collected data.
- **run.sh**: Script to run the main program and save data.
- **serial_linux.c / serial_linux.h**: Code for serial communication with the Arduino.
- **utils.c / utils.h**: Utility functions.

## Getting Started

### Prerequisites

Ensure you have the following installed:
- Arduino IDE
- GCC (GNU Compiler Collection) for compiling C code on Linux
- Make
- Gnuplot (for plotting, if applicable)

### Setting Up the Arduino

1. Navigate to the `arduino` directory:
   ```bash
   cd arduino
   ```
2. Compile and flash (on dev/ttyUSB0) the Arduino code:
	```bash
	./compile.sh
	```

### Setting Up on Linux

1. Navigate to the `linux` directory:
   ```bash
   cd linux
   ```
2. Compile the Linux code:
	```bash
	./compile.sh
	```
3. Run the main program:
	```bash
	./run.sh
	```
4. To plot the data, use:
	```bash
	./plot.sh
	```

## Usage

- Connect the Arduino to your Linux system via USB.
- Run the main program to start collecting data.
- Use the provided script to plot and analyze the data.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

