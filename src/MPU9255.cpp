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
  uint8_t rawData[6];//bufor
  for(char i = 0;i<6;i++)
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
  for(char i = 0;i<6;i++)
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
  for(char i = 0;i<6;i++)
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

  uint8_t rawData[2];
  for(char i = 0;i<2;i++)
  {
    rawData[i++] = Wire.read();//read byte and put it into rawData table
  }

  int16_t temp=0;
  temp = ((int16_t)rawData[0] << 8) | rawData[1];//put together the output value
  return temp;//return raw data
}
