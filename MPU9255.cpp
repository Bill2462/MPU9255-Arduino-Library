/*
Copyright (C) Bill2462 from https://github.com/Bill2462
 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 3 as published by the Free Software Foundation.

*/

#include "MPU9255.h" 
#include "Arduino.h"

//############################################# Private functions ############################################# 
// variables 

uint16_t mx=0;
uint16_t my=0;
uint16_t mz=0;

uint8_t MPU9255::read(uint8_t address, uint8_t subAddress)
{

  uint8_t data;
  Wire.beginTransmission(address); 
  Wire.write(subAddress); 
  Wire.endTransmission(false); 
  Wire.requestFrom(address, (uint8_t) 1);
  data = Wire.read(); 
  return data;
}

void MPU9255::write(uint8_t address, uint8_t subAddress, uint8_t data)
{

  Wire.beginTransmission(address); 
  Wire.write(subAddress); 
  Wire.write(data); 
  Wire.endTransmission(); 
}

//############################################# Public functions #############################################

void MPU9255::init()
{
  Wire.begin();
// MPU9255 init procedure 
  write(MPU_adress,PWR_MGMT_2, 0b11111111); // enable gyro and acc 
  write(MPU_adress,CONFIG, 0x03); // set DLPF_CFG to 11 
  write(MPU_adress,SMPLRT_DIV, 0x04);// set prescaler sample rate to 4 
  uint8_t c = read(MPU_adress,GYRO_CONFIG); 
  write(MPU_adress,GYRO_CONFIG, c & ~0x02);// set second option from tavle 
  write(MPU_adress,GYRO_CONFIG, c & ~0x18);// set scale to +- 250 dps
  c = read(MPU_adress,ACCEL_CONFIG); 
  write(MPU_adress,ACCEL_CONFIG, c & ~0x18); // set scale to +- 2G 
  
  write(MPU_adress,INT_PIN_CFG, 0x22);// BYPASS ENABLE, LATCH_INT_EN 
  write(MPU_adress,INT_ENABLE, 0x01); // RAW_RDY_EN 

// magnetometer init procedure 
  write(MAG_adress, CNTL, 0x00);
  write(MAG_adress, CNTL, 0x16); 

}

int16_t MPU9255::get_ax()
{
  uint16_t data;
  uint8_t rawData[2]; 
  rawData[0]=read(MPU_adress,ACCEL_XOUT_H);
  rawData[1]=read(MPU_adress,ACCEL_XOUT_L);
  data=((int16_t)rawData[0] << 8) | rawData[1];
  return data;
}

int16_t MPU9255::get_ay()
{
  uint16_t data;
  uint8_t rawData[2]; 
  rawData[0]=read(MPU_adress,ACCEL_YOUT_H);
  rawData[1]=read(MPU_adress,ACCEL_YOUT_L);
  data=((int16_t)rawData[0] << 8) | rawData[1];
  return data;
}

int16_t MPU9255::get_az()
{
  uint16_t data;
  uint8_t rawData[2]; 
  rawData[0]=read(MPU_adress,ACCEL_ZOUT_H);
  rawData[1]=read(MPU_adress,ACCEL_ZOUT_L);
  data=((int16_t)rawData[0] << 8) | rawData[1];
  return data;
}

int16_t MPU9255::get_gx()
{
  uint16_t data;
  uint8_t rawData[2]; 
  rawData[0]=read(MPU_adress,GYRO_XOUT_H);
  rawData[1]=read(MPU_adress,GYRO_XOUT_L);
  data=((int16_t)rawData[0] << 8) | rawData[1];
  return data;
}

int16_t MPU9255::get_gy()
{
  uint16_t data;
  uint8_t rawData[2]; 
  rawData[0]=read(MPU_adress,GYRO_YOUT_H);
  rawData[1]=read(MPU_adress,GYRO_YOUT_L);
  data=((int16_t)rawData[0] << 8) | rawData[1];
  return data;
}

int16_t MPU9255::get_gz()
{
  uint16_t data;
  uint8_t rawData[2]; 
  rawData[0]=read(MPU_adress,GYRO_ZOUT_H);
  rawData[1]=read(MPU_adress,GYRO_ZOUT_L);
  data=((int16_t)rawData[0] << 8) | rawData[1];
  return data;
}

void MPU9255::read_mag()
{
    uint8_t rawData[6]; 
    read(MAG_adress, ST1);

    //readBytes(AK8963_ADDRESS, AK8963_XOUT_L, 8, &rawData[0]);
// get some data 
  Wire.beginTransmission(MAG_adress); 
  Wire.write(MAG_XOUT_L); 
  Wire.endTransmission(false); 
  uint8_t i = 0;
  Wire.requestFrom(MAG_adress, 8); 
  while (Wire.available()) {
    rawData[i++] = Wire.read();
  } 
// process data 
mx=((int16_t)rawData[1] << 8) | rawData[0] ;
my=((int16_t)rawData[3] << 8) | rawData[2] ;
mz=((int16_t)rawData[5] << 8) | rawData[4] ;
}

int16_t MPU9255::get_mx()
{
  return mx;
}

int16_t MPU9255::get_my()
{
  return my; 
}

int16_t MPU9255::get_mz()
{
  return mz;
}
