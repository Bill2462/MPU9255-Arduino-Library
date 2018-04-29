# MPU9255-Arduino-Library
[![Build Status](https://travis-ci.org/Bill2462/MPU9255-Arduino-Library.svg?branch=master)](https://travis-ci.org/Bill2462/MPU9255-Arduino-Library)
[![GitHub release](https://img.shields.io/github/release/Bill2462/MPU9255-Arduino-Library.svg?maxAge=3600)](https://github.com/Bill2462/MPU9255-Arduino-Library/releases/latest)
[![License](https://img.shields.io/github/license/Bill2462/MPU9255-Arduino-Library.svg?maxAge=3600)](LICENSE)

Arduino library for MPU9255 based modules. 


Read acceleration, angular velocity and magnetic field strength on your Arduino board using MPU9266 based IMU module connected via the I2C interface. 

## Features
- Acceleration, angular velocity, magnetic field measurements. 
- Dice temperature measurements using build-in sensor.
- Selectable scale (from +- 2g , +- 250 dps to +- 16g , +-2000 dps).
- Selectable bandwidth for gyroscope and accelerometer. 
- Power control (sleep mode, enabling / disabling internal components). 
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

## Library documentation
https://github.com/Bill2462/MPU9255-Arduino-Library/blob/master/doc/index.md
