#include "MPU9255.h"
#include "Arduino.h"

int16_t MPU9255::uint8ToUint16(uint8_t Lbyte, uint8_t Hbyte)
{
  return ((int16_t)Hbyte << 8) | Lbyte;
}

/* Read data from the accelerometer
Arguments: None
Returns : None
*/
void MPU9255::read_acc()
{
  requestBytes(MPU_address, ACCEL_XOUT_H, 6);//request data from the accelerometer

  uint8_t rawData[6];
  readArray(rawData,6);

  ax = uint8ToUint16(rawData[1], rawData[0]);
  ay = uint8ToUint16(rawData[3], rawData[2]);
  az = uint8ToUint16(rawData[5], rawData[4]);
}

/* Read data from the gyroscope
Arguments: None
Returns : None
*/
void MPU9255::read_gyro()
{
  requestBytes(MPU_address, GYRO_XOUT_H, 6);

  uint8_t rawData[6];//bufor
  readArray(rawData,6);

  //dump reading into output variables
  gx = uint8ToUint16(rawData[1], rawData[0]);
  gy = uint8ToUint16(rawData[3], rawData[2]);
  gz = uint8ToUint16(rawData[5], rawData[4]);
}

/* Read data from the magnetometer
Arguments: None
Returns : None
*/
void MPU9255::read_mag()
{
  requestBytes(MAG_address, MAG_XOUT_L, 6);

  uint8_t rawData[6];
  readArray(rawData,6);

  mx = uint8ToUint16(rawData[1], rawData[0]);
  my = uint8ToUint16(rawData[3], rawData[2]);
  mz = uint8ToUint16(rawData[5], rawData[4]);
}

int16_t MPU9255::read_temp()
{
  requestBytes(MAG_address, TEMP_OUT_H, 2);

  uint8_t rawData[2];
  readArray(rawData,2);

  return uint8ToUint16(rawData[1], rawData[0]);
}
