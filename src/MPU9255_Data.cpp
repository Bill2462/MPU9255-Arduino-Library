/*
MPU9255_Data.cpp - Measurements functions
*/

#include "MPU9255.h"
#include "Arduino.h"

//convert two bytes to int16_t value
//parameters:
// * uint8_t Lbyte - low byte
// * uint8_t Hbyte - high byte
//Returns : converted value (int16_t)
int16_t MPU9255::uint8ToUint16(uint8_t Lbyte, uint8_t Hbyte)
{
  return ((int16_t)Hbyte << 8) | Lbyte;
}

//read accelerometer data registers
void MPU9255::read_acc()
{
  requestBytes(MPU_address, ACCEL_XOUT_H, 6);//request data from the accelerometer

  //read data
  uint8_t rawData[6];
  readArray(rawData,6);

  //store data in raw data variables
  ax = uint8ToUint16(rawData[1], rawData[0]);
  ay = uint8ToUint16(rawData[3], rawData[2]);
  az = uint8ToUint16(rawData[5], rawData[4]);
}

//read gyroscope data registers
void MPU9255::read_gyro()
{
  requestBytes(MPU_address, GYRO_XOUT_H, 6);

  uint8_t rawData[6];
  readArray(rawData,6);

  gx = uint8ToUint16(rawData[1], rawData[0]);
  gy = uint8ToUint16(rawData[3], rawData[2]);
  gz = uint8ToUint16(rawData[5], rawData[4]);
}

//read magnetometer data registers
void MPU9255::read_mag()
{
  requestBytes(MAG_address, MAG_XOUT_L, 8);//note we must request 8 bytes of data because otherwise it does not work

  uint8_t rawData[6];
  readArray(rawData,6);

  //dump reading into output variables
  mx = uint8ToUint16(rawData[0], rawData[1]);
  my = uint8ToUint16(rawData[2], rawData[3]);
  mz = uint8ToUint16(rawData[4], rawData[5]);
}

//read temperature
//Returns : temperature
int16_t MPU9255::read_temp()
{
  requestBytes(MPU_address, TEMP_OUT_H, 2);

  uint8_t rawData[2];
  readArray(rawData,2);

  return uint8ToUint16(rawData[1], rawData[0]);
}
