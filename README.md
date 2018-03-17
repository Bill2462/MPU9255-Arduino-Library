[![Build Status](https://travis-ci.org/Bill2462/MPU9255-Arduino-Library.svg?branch=V0.3)](https://travis-ci.org/Bill2462/MPU9255-Arduino-Library)

# MPU9255-Arduino-Library

Arduino library for MPU9255 accelerometer / gyroscope / magnetometer chip.

## Features
- Acceleration / angular velocity / magnetic flux measurements.
- Temperature measurements through an internal sensor. (experimental).
- Scale selection (from +- 2g and +- 250 dps to +- 16g and +-2000 dps).
- Power reduction.
- Reset control.

## Installation
1. Download library in a zip archive (Clone or download -> download zip).
2. Launch Arduino IDE.
3. Go to sketch -> include library and press add zip. library.
4. Select downloaded archive and click open.

## Examples
Library contains 4 examples :
- rawData : Reads raw data from the sensors.
- dataProcessing : Reads data and processes them to get some useful information.
- scaleExample : Demonstrates all available scales.

## Library reference

https://github.com/Bill2462/MPU9255-Arduino-Library/wiki

Note: Library was tested with Waveshare IMU 10DoF module.
