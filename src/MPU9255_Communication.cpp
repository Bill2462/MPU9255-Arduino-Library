/**
 * @file MPU9255_Communications.cpp
 * @brief This source file contains methods for reading and writing to the device.
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

//Request data
//Parameters:
// * uint8_t address    - address of the device
// * uint8_t subAddress - address of the register (the read starts from that register)
// * uint8_t bytes      - number of requested bytes
void MPU9255::requestBytes(uint8_t address, uint8_t subAddress, uint8_t bytes)
{
  Wire.beginTransmission(address);
  Wire.write(subAddress);
  Wire.endTransmission(false);
  Wire.requestFrom(address, bytes);
}

//read an array of bytes from the device
//Parameters:
// * uint8_t *output - pointer to the output array
// * char size       - number of bytes to read
void MPU9255::readArray(uint8_t *output, char size)
{
  for(char i = 0; i<size; i++)
  {
    output[i] = Wire.read();//read byte and put it into rawData table
  }
}

//Read one byte of data
//Parameters:
// * uint8_t address    - device address
// * uint8_t subAddress - register address
//Returns : Readed byte of data (uint8_t)
uint8_t MPU9255::read(uint8_t address, uint8_t subAddress)
{
  requestBytes(address,subAddress,1);//request one byte from the register
  uint8_t data = Wire.read();//read one byte of data
  return data;
}

// Write one byte of data
//Parameters:
// * uint8_t address    - device address
// * uint8_t subAddress - register address
// * uint8_t data       - one byte of data that we want to put in the register
void MPU9255::write(uint8_t address, uint8_t subAddress, uint8_t data)
{
  Wire.beginTransmission(address);
  Wire.write(subAddress);
  Wire.write(data);
  Wire.endTransmission();
}

//Change state of the register using OR operation
//Parameters:
// * uint8_t address    - device address
// * uint8_t subAddress - register address
// * uint8_t data       - one byte of data that we want to put in the register
void MPU9255::write_OR(uint8_t address, uint8_t subAddress, uint8_t data)
{
  uint8_t c = read(address,subAddress);
  c = c | data;
  write(address,subAddress,c);
}

//Change state of the register using AND operation
//Parameters:
// * uint8_t address    - device address
// * uint8_t subAddress - register address
// * uint8_t data       - one byte of data that we want to put in the register
void MPU9255::write_AND(uint8_t address, uint8_t subAddress, uint8_t data)
{
  uint8_t c = read(address,subAddress);
  c = c & data;
  write(address,subAddress,c);
}
