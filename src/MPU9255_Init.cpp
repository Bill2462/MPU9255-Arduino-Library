#include "MPU9255.h"
#include "Arduino.h"

/* Initialize the chip
Arguments: None
Returns : None
*/
void MPU9255::init()
{
  Wire.begin();// enable I2C interface
  write(MPU_address,CONFIG, 0x03); // set DLPF_CFG to 11
  write(MPU_address,SMPLRT_DIV, 0x04);// set prescaler sample rate to 4
  write(MPU_address,GYRO_CONFIG, 0x01);// set gyro to 3.6 KHz bandwidth, and 0.11 ms using FCHOICE bits
  write(MPU_address,INT_PIN_CFG, 0x02);// BYPASS ENABLE (Necessary for the magnetometer to function)
  write(MAG_address, CNTL, 0x16);//set magnetometer to read in mode 2 and enable 16 bit measurements

  ///read magnetometer sensitivity for compensation
  mx_sensitivity = (((read(MAG_address, ASAX)-128)*0.5)/128)+1;
  my_sensitivity = (((read(MAG_address, ASAY)-128)*0.5)/128)+1;
  mz_sensitivity = (((read(MAG_address, ASAZ)-128)*0.5)/128)+1;
}
