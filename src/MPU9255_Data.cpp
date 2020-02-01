/**
 * @file MPU9255_Data.cpp
 * @brief This source file contains methods for taking readings from
 * IMU and magnetometer.
 */

// This file is a part of MPU9255 library.
// Copyright (c) 2017-2020 Krzysztof Adamkiewicz <kadamkiewicz835@gmail.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the “Software”), to deal in the
// Software without restriction, including without limitation the rights to use, copy,
// modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
// and to permit persons to whom the Software is furnished to do so, subject to the
// following conditions: THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
// OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include "MPU9255.h"
#include "Arduino.h"

/**
 * @brief Read readings from accelerometer.
 */
void MPU9255::read_acc()
{
  requestBytes(MPU_address, ACCEL_XOUT_H, 6);//request data from the accelerometer

  //read data
  uint8_t rawData[6];
  readArray(rawData,6);

  //store data in raw data variables
  ax = ((int16_t)rawData[0] << 8) | rawData[1];
  ay = ((int16_t)rawData[2] << 8) | rawData[3];
  az = ((int16_t)rawData[4] << 8) | rawData[5];
}

/**
 * @brief Read readings from gyroscope.
 */
void MPU9255::read_gyro()
{
  requestBytes(MPU_address, GYRO_XOUT_H, 6);

  uint8_t rawData[6];
  readArray(rawData,6);
  
  gx = ((int16_t)rawData[0] << 8) | rawData[1];
  gy = ((int16_t)rawData[2] << 8) | rawData[3];
  gz = ((int16_t)rawData[4] << 8) | rawData[5];
}

/**
 * @brief Read readings from magnetometer.
 */
void MPU9255::read_mag()
{
  requestBytes(MAG_address, MAG_XOUT_L, 8);//note we must request 8 bytes of data because otherwise it does not work

  uint8_t rawData[6];
  readArray(rawData,6);

  mx = ((int16_t)rawData[0] << 8) | rawData[1];
  my = ((int16_t)rawData[2] << 8) | rawData[3];
  mz = ((int16_t)rawData[4] << 8) | rawData[5];
}

/**
 * @brief Take a reading of the temperature.
 * @return Temperature.
 */
int16_t MPU9255::read_temp()
{
  requestBytes(MPU_address, TEMP_OUT_H, 2);

  uint8_t rawData[2];
  readArray(rawData,2);

  return ((int16_t)rawData[0] << 8) | rawData[1];
}
