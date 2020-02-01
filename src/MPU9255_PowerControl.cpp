/**
 * @file MPU9255_PowerControl.cpp
 * @brief This source file contains methods for power control.
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

// perform hard reset (all regesters will be restored to they default values )
void MPU9255::Hreset()
{
  write_OR(MPU_address,PWR_MGMT_1,1<<7);//set reset bit in PWR_MGMT_1 register
}

//enable sleep mode
void MPU9255::sleep_enable()
{
  write_OR(MPU_address,PWR_MGMT_1, 1<<6);//set sleep bit in PWR_MGMT_1 register
}

//disable sleep mode
void MPU9255::sleep_disable()
{
  write_AND(MPU_address,PWR_MGMT_1, ~(1<<6));//clear sleep bit in PWR_MGMT_1 register
}

//reset selected module
//parameters:
// * modules selected_module - selected module
void MPU9255::reset(modules selected_module)
{
  switch(selected_module)
  {
    case accelerometer:
      write_OR(MPU_address,SIGNAL_PATH_RESET, 1<<1);
      break;

    case gyroscope:
      write_OR(MPU_address,SIGNAL_PATH_RESET, 1<<2);
      break;

    case thermometer:
      write_OR(MPU_address,SIGNAL_PATH_RESET, 1<<0);
      break;

    case signalPaths:
      write_OR(MPU_address,USER_CTRL, 1<<0);
      break;

    case magnetometer:
      write_OR(MAG_address,CNTL2, 1<<0);
      break;
  }
}

//disable selected_module
//parameters:
// * modules selected_module - selected module
void MPU9255::disable(modules selected_module)
{
  switch (selected_module)
  {
    case Acc_X:
      write_OR(MPU_address,PWR_MGMT_2, 1<<5);
      break;

    case Acc_Y:
      write_OR(MPU_address,PWR_MGMT_2, 1<<4);
      break;

    case Acc_Z:
      write_OR(MPU_address,PWR_MGMT_2, 1<<3);
      break;

    case Gyro_X:
      write_OR(MPU_address,PWR_MGMT_2, 1<<2);
      break;

    case Gyro_Y:
      write_OR(MPU_address,PWR_MGMT_2, 1<<1);
      break;

    case Gyro_Z:
      write_OR(MPU_address,PWR_MGMT_2, 1<<0);
      break;

    case magnetometer:
      write(MAG_address,CNTL, 0x00);
      break;
  }
}

//enable selected_module
//parameters:
// * modules selected_module - selected module
void MPU9255::enable(modules selected_module)
{
  switch (selected_module)
  {
    case Acc_X:
      write_AND(MPU_address,PWR_MGMT_2, ~(1<<5));
      break;

    case Acc_Y:
      write_AND(MPU_address,PWR_MGMT_2, ~(1<<4));
      break;

    case Acc_Z:
      write_AND(MPU_address,PWR_MGMT_2, ~(1<<3));
      break;

    case Gyro_X:
      write_AND(MPU_address,PWR_MGMT_2, ~(1<<2));
      break;

    case Gyro_Y:
      write_AND(MPU_address,PWR_MGMT_2, ~(1<<1));
      break;

    case Gyro_Z:
      write_AND(MPU_address,PWR_MGMT_2, ~(1<<0));
      break;

    case magnetometer:
      write(MAG_address,CNTL, 0x16);
      break;
  }
}
