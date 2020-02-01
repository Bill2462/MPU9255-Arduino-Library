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

/**
 * @brief Request data from the specific region in the device memory.
 * @param address Address of the device.
 * @param subAddress  Address of the device memory.
 * @param bytes Number of bytes that we want to request from the device.
 */
void MPU9255::requestBytes(uint8_t address, uint8_t subAddress, uint8_t bytes)
{
  Wire.beginTransmission(address);
  Wire.write(subAddress);
  Wire.endTransmission(false);
  Wire.requestFrom(address, bytes);
}

/**
 * @brief Read the array of bytes from the device.
 * @note Array has to be first requested using requestBytes method.
 * @param output Pointer to the array where the received bytes will be written.
 * @param size How many bytes we want to read.
 */
void MPU9255::readArray(uint8_t* output, char size)
{
  for(char i = 0; i<size; i++)
  {
    output[i] = Wire.read();//read byte and put it into rawData table
  }
}

/**
 * @brief Read a single byte from the register
 * @param address Device address.
 * @param subAddress Address of the memory
 * @return Red byte.
 */
uint8_t MPU9255::read(uint8_t address, uint8_t subAddress)
{
  requestBytes(address,subAddress,1);//request one byte from the register
  uint8_t data = Wire.read();//read one byte of data
  return data;
}

/**
 * @brief Write a single byte to the register.
 * @param address Device address.
 * @param subAddress Address of the memory.
 * @param data Value that we want to put in the register.
 */
void MPU9255::write(uint8_t address, uint8_t subAddress, uint8_t data)
{
  Wire.beginTransmission(address);
  Wire.write(subAddress);
  Wire.write(data);
  Wire.endTransmission();
}

/**
 * @brief Change state of the register using OR operation
 * @param address device address
 * @param subAddress register address
 * @param data data
 */
void MPU9255::write_OR(uint8_t address, uint8_t subAddress, uint8_t data)
{
  uint8_t c = read(address,subAddress);
  c = c | data;
  write(address,subAddress,c);
}

/**
 * @brief Change state of the register using AND operation
 * @param address device address
 * @param subAddress register address
 * @param data data
 */
void MPU9255::write_AND(uint8_t address, uint8_t subAddress, uint8_t data)
{
  uint8_t c = read(address,subAddress);
  c = c & data;
  write(address,subAddress,c);
}
