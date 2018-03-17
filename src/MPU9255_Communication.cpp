#include "MPU9255.h"
#include "Arduino.h"


void MPU9255::requestBytes(uint8_t address, uint8_t subAddress, uint8_t bytes)
{
  Wire.beginTransmission(address);
  Wire.write(subAddress);
  Wire.endTransmission(false);
  Wire.requestFrom(address, bytes);
}

void MPU9255::readArray(uint8_t *output, char size)
{
  for(char i = 0; i<size; i++)
  {
    output[i] = Wire.read();//read byte and put it into rawData table
  }
}

/* Read one byte of data from the sensor
Arguments:
- address - address of the device
- subAddress - address of the register
Returns : Contents of the readed register (one byte)
*/
uint8_t MPU9255::read(uint8_t address, uint8_t subAddress)
{
  uint8_t data;
  requestBytes(address,subAddress,1);
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
