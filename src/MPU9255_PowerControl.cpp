#include "MPU9255.h"
#include "Arduino.h"

/* Perform hard reset (basically reset everything). Call of init() function is required to use sensor afterwards
Arguments: None
Returns : None
*/
void MPU9255::Hreset()
{
  write(MPU_address,PWR_MGMT_1, 0x80);//write 1 to the hard reset bit in PWR_MGMT_1 register
}

/* Put main chip in a sleep mode
Arguments: None
Returns : None
*/
void MPU9255::sleep_enable()
{
  write(MPU_address,PWR_MGMT_1, 0x40);//set sleep bit to 1
}

/* disable sleep mode
Arguments: None
Returns : None
*/
void MPU9255::sleep_disable()
{
  write(MPU_address,PWR_MGMT_1, 0x00);//clear the sleep bit
  delay(500);//wait until module stabilizes
}

void MPU9255::reset(modules selected_module)
{
  if(selected_module == accelerometer)
  {
    write(MPU_address,SIGNAL_PATH_RESET, 0x02);
  }

  if(selected_module == gyroscope)
  {
    write(MPU_address,SIGNAL_PATH_RESET, 0x04);
  }

  if(selected_module == thermometer)
  {
    write(MPU_address,SIGNAL_PATH_RESET, 0x01);
  }

  if(selected_module == signalPaths)
  {
      write_OR(MPU_address,USER_CTRL, 0x01);
  }

  if(selected_module == magnetometer)
  {
      write(MAG_address,CNTL2, 0x01);
  }
}

void MPU9255::disable(modules selected_module)
{
  if(selected_module == Acc_X)
  {
    write_OR(MPU_address,PWR_MGMT_2, 0x20);
  }

  if(selected_module == Acc_Y)
  {
    write_OR(MPU_address,PWR_MGMT_2, 0x10);
  }

  if(selected_module == Acc_Z)
  {
    write_OR(MPU_address,PWR_MGMT_2, 0x08);
  }

  if(selected_module == Gyro_X)
  {
    write_OR(MPU_address,PWR_MGMT_2, 0x04);
  }

  if(selected_module == Gyro_Y)
  {
    write_OR(MPU_address,PWR_MGMT_2, 0x02);
  }

  if(selected_module == Gyro_Z)
  {
    write_OR(MPU_address,PWR_MGMT_2, 0x01);
  }

  if(selected_module == magnetometer)
  {
    write(MAG_address,CNTL, 0x00);
  }

}

void MPU9255::enable(modules selected_module)
{
  if(selected_module == Acc_X)
  {
    write_AND(MPU_address,PWR_MGMT_2, ~0x20);
  }

  if(selected_module == Acc_Y)
  {
    write_AND(MPU_address,PWR_MGMT_2, ~0x10);
  }

  if(selected_module == Acc_Z)
  {
    write_AND(MPU_address,PWR_MGMT_2, ~0x8);
  }

  if(selected_module == Gyro_X)
  {
    write_AND(MPU_address,PWR_MGMT_2, ~0x04);
  }

  if(selected_module == Gyro_Y)
  {
    write_AND(MPU_address,PWR_MGMT_2, ~0x02);
  }

  if(selected_module == Gyro_Z)
  {
    write_AND(MPU_address,PWR_MGMT_2, ~0x01);
  }

  if(selected_module == magnetometer)
  {
    write(MAG_address,CNTL, 0x16);
  }
}
