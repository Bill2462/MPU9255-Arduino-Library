/*
Copyright (C) Bill2462 from https://github.com/Bill2462
 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 3 as published by the Free Software Foundation.
*/

#include "MPU9255.h"
#include "Arduino.h"

/* Read one byte of data from the sensor
Arguments:
- address - address of the device
- subAddress - address of the register
Returns : Contents of the readed register (one byte)
*/
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

/* Write one byte to the register
Arguments:
- address - address of the device
- subAddress - address of the register
- data - one byte of data that we want to put in the register
Returns : None
*/
void MPU9255::write(uint8_t address, uint8_t subAddress, uint8_t data)
{
  Wire.beginTransmission(address);
  Wire.write(subAddress);
  Wire.write(data);
  Wire.endTransmission();
}

/* Perform OR operation on a register state and a data byte and write
result into the register.
t
Arguments:
- address - address of the device
- subAddress - address of the register
- data - one byte of data that we want to put in the register
Returns : None
*/
void MPU9255::write_OR(uint8_t address, uint8_t subAddress, uint8_t data)
{
  uint8_t c = read(address,subAddress);
  c = c | data;
  write(address,subAddress,c);
}

/* Perform AND operation on a register state and a data byte and write
result into the register.
Arguments:
- address - address of the device
- subAddress - address of the register
- data - one byte of data that we want to put in the register
Returns : None
*/
void MPU9255::write_AND(uint8_t address, uint8_t subAddress, uint8_t data)
{
  uint8_t c = read(address,subAddress);
  c = c & data;
  write(address,subAddress,c);
}

/* Initialize the chip
Arguments: None
Returns : None
*/
void MPU9255::init()
{
  Wire.begin();// enable I2C interface
  Hreset();//reset the chip
  write(MPU_adress,CONFIG, 0x03); // set DLPF_CFG to 11
  write(MPU_adress,SMPLRT_DIV, 0x04);// set prescaler sample rate to 4
  write(MPU_adress,GYRO_CONFIG, 0x01);// set gyro to 3.6 KHz bandwidth, and 0.11 ms using FCHOICE bits
  write(MPU_adress,INT_PIN_CFG, 0x02);// BYPASS ENABLE (Necessary for the magnetometer to function)
  write(MAG_adress, CNTL, 0x16);//set magnetometer to read in mode 2 and enable 16 bit measurements
}

/* Set accelerometer scale
Arguments:
- Selected scale
Returns : None
*/
void MPU9255::set_acc_scale(unsigned char value)
{
	uint8_t val = read(MPU_adress,ACCEL_CONFIG);//read old register value
	switch(value)
	{
		case 1:// +- 2g
		val &= ~((1<<3)|(1<<4));
		break;

		case 2:// +- 4g
		val &= ~(1<<4);
		val |= (1<<3);
		break;

		case 3:// +- 8g
		val &= ~(1<<3);
		val |= (1<<4);
		break;

		case 4:// +- 16g
		val |= (1<<4)|(1<<3);
		break;
	}
	write(MPU_adress,ACCEL_CONFIG,val);// commit changes
}

/* Set gyroscope scale
Arguments:
- Selected scale
Returns : None
*/
void MPU9255::set_gyro_scale(unsigned char value)
{
	uint8_t val=read(MPU_adress,GYRO_CONFIG);//read old register value
	switch(value)
	{
		case 1:// +- 250 dps
		val &= ~((1<<3)|(1<<4));
		break;

		case 2:// +- 500 dps
		val &= ~(1<<4);
		val |= (1<<3);
		break;

		case 3:// +- 1000 dps
		val &= ~(1<<3);
		val |= (1<<4);
		break;

		case 4:// +- 2000 dps
		val |= (1<<4)|(1<<3);
		break;
	}
	write(MPU_adress,GYRO_CONFIG,val);// commit changes
}

/* Read data from the accelerometer
Arguments: None
Returns : None
*/
void MPU9255::read_acc()
{
  //request data
  Wire.beginTransmission(MPU_adress);//begin transmission to the sensor
  Wire.write(ACCEL_XOUT_H);//write adress of the accelerometer data register to signalize that we want to read it
  Wire.endTransmission(false);//end transmission
  Wire.requestFrom(MPU_adress, 6);//request 6 bytes of data from the sensor

  //read data
  uint8_t i = 0;//index
  uint8_t rawData[6];//bufor
  while (Wire.available())//loop throught all received bytes
  {
    rawData[i++] = Wire.read();//read byte and put it into rawData table
  }

  //dump reading into output variables
  ax = ((int16_t)rawData[0] << 8) | rawData[1] ;
  ay = ((int16_t)rawData[2] << 8) | rawData[3] ;
  az = ((int16_t)rawData[4] << 8) | rawData[5] ;
}

/* Read data from the gyroscope
Arguments: None
Returns : None
*/
void MPU9255::read_gyro()
{
  Wire.beginTransmission(MPU_adress);//begin transmission to the sensor
  Wire.write(GYRO_XOUT_H);//write adress of the accelerometer data register to signalize that we want to read it
  Wire.endTransmission(false);//end transmission
  Wire.requestFrom(MPU_adress, 6);//request 6 bytes of data from the sensor

  uint8_t rawData[6];//bufor
  uint8_t i = 0;//index
  while (Wire.available())//loop throught all received bytes
  {
    rawData[i++] = Wire.read();//read byte and put it into rawData table
  }

  //dump reading into output variables
  gx = ((int16_t)rawData[0] << 8) | rawData[1] ;
  gy = ((int16_t)rawData[2] << 8) | rawData[3] ;
  gz = ((int16_t)rawData[4] << 8) | rawData[5] ;
}

/* Read data from the magnetometer
Arguments: None
Returns : None
*/
void MPU9255::read_mag()
{
  Wire.beginTransmission(MAG_adress);//begin transmission to the sensor
  Wire.write(MAG_XOUT_L);//write adress of the accelerometer data register to signalize that we want to read it
  Wire.endTransmission(false);//end transmission
  Wire.requestFrom(MAG_adress, 8);//request 6 bytes of data from the sensor

  uint8_t rawData[6];//bufor
  uint8_t i = 0;//index
  while (Wire.available())//loop throught all received bytes
  {
    rawData[i++] = Wire.read();//read byte and put it into rawData table
  }

  //dump reading into output variables
  mx=((int16_t)rawData[1] << 8) | rawData[0] ;
  my=((int16_t)rawData[3] << 8) | rawData[2] ;
  mz=((int16_t)rawData[5] << 8) | rawData[4] ;
}

int16_t MPU9255::read_temp()
{
  Wire.beginTransmission(MPU_adress);//begin transmission to the sensor
  Wire.write(TEMP_OUT_H);//write adress of the thermometer data register to signalize that we want to read it
  Wire.endTransmission(false);//end transmission
  Wire.requestFrom(MPU_adress, 2);//request 2 bytes of data from the sensor

  uint8_t rawData[2];//bufor
  uint8_t i = 0;//index
  while (Wire.available())//loop throught all received bytes
  {
    rawData[i++] = Wire.read();//read byte and put it into rawData table
  }

  int16_t temp=0;
  temp = ((int16_t)rawData[0] << 8) | rawData[1];//put together the output value
  return temp;//return raw data
}

/* Perform hard reset (basically reset everything). Call of init() function is required to use sensor afterwards
Arguments: None
Returns : None
*/
void MPU9255::Hreset()
{
  write(MPU_adress,PWR_MGMT_1, 0x80);//write 1 to the hard reset bit in PWR_MGMT_1 register
}

/* Reset signal patch of the gyroscope
Arguments: None
Returns : None
*/
void MPU9255::gyro_RST()
{
  write(MPU_adress,SIGNAL_PATH_RESET, 0x04);
}

/* Reset signal patch of the accelerometer
Arguments: None
Returns : None
*/
void MPU9255::acc_RST()
{
  write(MPU_adress,SIGNAL_PATH_RESET, 0x02);
}

/* Reset signal patch of the thermometer
Arguments: None
Returns : None
*/
void MPU9255::temp_RST()
{
  write(MPU_adress,SIGNAL_PATH_RESET, 0x01);
}

/* Reset accelerometer, gyroscope and thermometer sygnal patches and registers
Arguments: None
Returns : None
*/
void MPU9255::SIG_COND_RST()
{
  uint8_t c = read(MPU_adress,USER_CTRL);//read old register value
  c = c | 0x01;//set bit 0 to 1
  write(MPU_adress,USER_CTRL, c);//commit changes
}

/* Perform software reset of the magnetometer
Arguments: None
Returns : None
*/
void MPU9255::mag_SoftRST()
{
  write(MAG_adress,CNTL2, 0x01);
}

/* Power down the magnetometer
Arguments: None
Returns : None
*/
void MPU9255::mag_PWRD()
{
  write(MAG_adress,CNTL, 0x00);
}

/* Power up magnetometer
Arguments: None
Returns : None
*/
void MPU9255::mag_PWRU()
{
  write(MAG_adress,CNTL, 0x16);
}

/* Put main chip in a sleep mode
Arguments: None
Returns : None
*/
void MPU9255::sleep_enable()
{
  write(MPU_adress,PWR_MGMT_1, 0x40);//set sleep bit to 1
}

/* disable sleep mode
Arguments: None
Returns : None
*/
void MPU9255::sleep_disable()
{
  write(MPU_adress,PWR_MGMT_1, 0x00);//clear the sleep bit
  delay(500);//wait until module stabilizes
}

/* disable accelerometer X axis
Arguments: None
Returns : None
*/
void MPU9255::disable_ax()
{
  write_OR(MPU_adress,PWR_MGMT_2, 0x20);
}

/* disable accelerometer Y axis
Arguments: None
Returns : None
*/
void MPU9255::disable_ay()
{
  write_OR(MPU_adress,PWR_MGMT_2, 0x10);
}

/* disable accelerometer Z axis
Arguments: None
Returns : None
*/
void MPU9255::disable_az()
{
  write_OR(MPU_adress,PWR_MGMT_2, 0x08);
}

/* disable gyroscope X axis
Arguments: None
Returns : None
*/
void MPU9255::disable_gx()
{
  write_OR(MPU_adress,PWR_MGMT_2, 0x04);
}

/* disable gyroscope Y axis
Arguments: None
Returns : None
*/
void MPU9255::disable_gy()
{
  write_OR(MPU_adress,PWR_MGMT_2, 0x02);
}

/* disable gyroscope Z axis
Arguments: None
Returns : None
*/
void MPU9255::disable_gz()
{
  write_OR(MPU_adress,PWR_MGMT_2, 0x01);
}

/* enable accelerometer X axis
Arguments: None
Returns : None
*/
void MPU9255::enable_ax()
{
  write_AND(MPU_adress,PWR_MGMT_2, ~0x20);
}

/* enable accelerometer Y axis
Arguments: None
Returns : None
*/
void MPU9255::enable_ay()
{
  write_AND(MPU_adress,PWR_MGMT_2, ~0x10);
}

/* enable accelerometer Y axis
Arguments: None
Returns : None
*/
void MPU9255::enable_az()
{
  write_AND(MPU_adress,PWR_MGMT_2, ~0x8);
}

/* enable accelerometer Z axis
Arguments: None
Returns : None
*/
void MPU9255::enable_gx()
{
  write_AND(MPU_adress,PWR_MGMT_2, ~0x04);
}

/* enable gyroscope Y axis
Arguments: None
Returns : None
*/
void MPU9255::enable_gy()
{
  write_AND(MPU_adress,PWR_MGMT_2, ~0x02);
}

/* enable gyroscope Z axis
Arguments: None
Returns : None
*/
void MPU9255::enable_gz()
{
  write_AND(MPU_adress,PWR_MGMT_2, ~0x01);
}
