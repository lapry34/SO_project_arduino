# Current Meter Arduino Project

## Overview
This project is designed for an operating systems course and involves using an Arduino to measure electrical current. The measured data is saved and can be accessed from a Linux system, where it can be plotted for analysis.

## Project Structure

The project is organized into three main directories: `arduino`, `linux` and `ML`.


## Arduino Directory

The `arduino` directory contains all the files necessary for running the current measurement on the Arduino. The key files include:

- **adc.c / adc.h**: Code for the Analog-to-Digital Converter.
- **arduino.c**: Main file for Arduino operations.
- **Makefile**: Makefile to facilitate the build process
- **avr.mk**: Makefile for AVR-specific settings.
- **uart.c / uart.h**: Code for UART communication.
- **timers.c / timers.h**: Timers initialization.
- **utils.c / utils.h**: Utility functions.

## Linux Directory

The `linux` directory contains the files needed to compile, run, and plot data on a Linux system. Key files include:

- **main.c**: Main file for Linux-side operations.
- **Makefile**: Makefile to facilitate the build process.
- **plot.sh**: Script to plot the collected data.
- **serial_linux.c / serial_linux.h**: Code for serial communication with the Arduino.
- **utils.c / utils.h**: Utility functions.

## ML Directory

The `ML` directory contains the files needed to train a Linear Regression model to fit the sample measuraments:
- **weights.py**: Script to train the ML model using Sklearn.
- **data.csv**: Data sampled during experiments.

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
	make
	```

### Setting Up on Linux

1. Navigate to the `linux` directory:
   ```bash
   cd linux
   ```
2. Compile and run the Linux code:
	```bash
	make
	```
3. To plot the data, use:
	```bash
	./plot.sh
	```

### Setting Up Machine Learning
1. Navigate to the `ML` directory:
   ```bash
   cd ML
   ```
2. Add measurements to data.csv.
3. Install requirements:
	```bash
	pip install -r requirements.txt
	```
3. Run the script:
	```bash
	python weights.py
	```

## Usage

- Connect the Arduino to your Linux system via USB.
- Run the main program to start collecting data.
- Use the provided script to plot and analyze the data.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Acknowledgements
Special thanks to [Prof. Grisetti](https://sites.google.com/dis.uniroma1.it/grisetti) and Dr. De Rebotti for the guidance and support throughout the course.

