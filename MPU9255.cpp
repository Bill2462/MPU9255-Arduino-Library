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
uint16_t ax=0;
uint16_t ay=0;
uint16_t az=0;

uint16_t gx=0;
uint16_t gy=0;
uint16_t gz=0;

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
  write(MPU_adress,PWR_MGMT_2, 0b00000000); // enable gyro and acc 
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

void MPU9255::set_acc_scale(unsigned char value)
{
	uint8_t val=read(MPU_adress,ACCEL_CONFIG);
	switch(value)
	{
		case 1:// +- 2g
		val &= ~((1<<3)|(1<<4));// set bit 3 and 4 to 0
		break;

		case 2:// +- 4g
		val &= ~(1<<4);// set bit 4 to zero
		val |= (1<<3);// set bit 3 to 1 
		break;

		case 3:// +- 8g
		val &= ~(1<<3);// set bit 3 to zero
		val |= (1<<4);// set bit 4 to 1 
		break;

		case 4:// +- 16g
		val |= (1<<4)|(1<<3);// set bit 3 and 4 to 1
		break;
	}
	write(MPU_adress,ACCEL_CONFIG,val);// commit changes 
}

void MPU9255::set_gyro_scale(unsigned char value)
{
	uint8_t val=read(MPU_adress,GYRO_CONFIG);
	switch(value)
	{
		case 1:// +- 250 dps
		val &= ~((1<<3)|(1<<4));// set bit 3 and 4 to 0
		break;

		case 2:// +- 500 dps
		val &= ~(1<<4);// set bit 4 to zero
		val |= (1<<3);// set bit 3 to 1 
		break;

		case 3:// +- 1000 dps
		val &= ~(1<<3);// set bit 3 to zero
		val |= (1<<4);// set bit 4 to 1 
		break;

		case 4:// +- 2000 dps
		val |= (1<<4)|(1<<3);// set bit 3 and 4 to 1
		break;
	}
	write(MPU_adress,GYRO_CONFIG,val);// commit changes 
}

void MPU9255::read_acc()
{

  uint8_t rawData[6];

  Wire.beginTransmission(MPU_adress); 
  Wire.write(ACCEL_XOUT_H); 
  Wire.endTransmission(false); 
  uint8_t i = 0;
  Wire.requestFrom(MPU_adress, 6); 
  while (Wire.available()) {
    rawData[i++] = Wire.read();
  } 
//data processing
  ax = ((int16_t)rawData[0] << 8) | rawData[1] ; 
  ay = ((int16_t)rawData[2] << 8) | rawData[3] ;
  az = ((int16_t)rawData[4] << 8) | rawData[5] ;
}

void MPU9255::read_gyro()
{
  uint8_t rawData[6];
  Wire.beginTransmission(MPU_adress); 
  Wire.write(GYRO_XOUT_H); 
  Wire.endTransmission(false); 
  uint8_t i = 0;
  Wire.requestFrom(MPU_adress, 6); 
  while (Wire.available()) {
    rawData[i++] = Wire.read();
  } 
//data processing
  gx = ((int16_t)rawData[0] << 8) | rawData[1] ; 
  gy = ((int16_t)rawData[2] << 8) | rawData[3] ;
  gz = ((int16_t)rawData[4] << 8) | rawData[5] ;
}

int16_t MPU9255::get_ax()
{
 return ax;
}

int16_t MPU9255::get_ay()
{
 return ay;
}

int16_t MPU9255::get_az()
{
 return az;
}

int16_t MPU9255::get_gx()
{
 return gx;
}

int16_t MPU9255::get_gy()
{
 return gy;
}

int16_t MPU9255::get_gz()
{
 return gy;
}

void MPU9255::read_mag()
{
  uint8_t rawData[6]; 
  read(MAG_adress, ST1);
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
