# MPU9255-Arduino-Library
[![Build Status](https://travis-ci.org/Bill2462/MPU9255-Arduino-Library.svg?branch=master)](https://travis-ci.org/Bill2462/MPU9255-Arduino-Library)
[![GitHub release](https://img.shields.io/github/release/Bill2462/MPU9255-Arduino-Library.svg?maxAge=3600)](https://github.com/Bill2462/MPU9255-Arduino-Library/releases/latest)
[![License](https://img.shields.io/github/license/Bill2462/MPU9255-Arduino-Library.svg?maxAge=3600)](LICENSE)

Arduino library for MPU9255 based modules.


Read acceleration, angular velocity and magnetic field strength on your Arduino board using MPU9255 based IMU module connected via the I2C interface.

## Features
- Acceleration, angular velocity, magnetic field measurements.
- Dice temperature measurements using built-in sensor.
- Selectable scale (from +- 2g , +- 250 dps to +- 16g , +-2000 dps).
- Selectable bandwidth for gyroscope and accelerometer.
- Power reduction support.
- Reset control.
- Motion interrupt support.

## Compatible IDE
Library is compatible with arduino IDE 1.6 or newer.

## Support/issue
- It seems to be a software issue.
  Please open an issue on github.

- It seems to be a hardware issue.
  Please ask in the official Arduino forum, where you will get a much faster answer than on github.

## Installation
1. Download library (Clone or download -> download zip).
2. Launch Arduino IDE.
3. Go to : sketch -> include library and select "add .zip library" option.
4. Select location of downloaded library and click "open".

## Connecting MPU9255 to arduino

| MPU9255       | Function       |
| ------------- | ------------- |
| VCC  | Power supply voltage  |
| GND  | Power supply ground  |
| SDA  | I2C data  line |
| SCL  | I2C clock  line |
| INT  | Interrupt digital output  |
| FSYNC|   Frame synchronisaion digital input**  |

** not supported by software. Connect to ground if unused. 

Minimal setup:

| MPU9255       | Arduino       |
| ------------- | ------------- |
| VCC  | Either 3.3V or 5v dependng on the module.**  |
| GND  | GND  |
| SDA  | SDA  |
| SCL  | SCL  |
| INT  | -    |
| FSYNC| GND  |

** MPU9255 requires 3.3V but some modules have 3.3V regulator built in. Please check your module documentation for more details.


## Library documentation
https://github.com/Bill2462/MPU9255-Arduino-Library/blob/master/doc/index.md
