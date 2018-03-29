/*
MPU9255_PowerControl.cpp - Power control functions
*/

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

//enbale selected_module
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
