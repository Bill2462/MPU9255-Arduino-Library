#include "MPU9255.h"
#include "Arduino.h"

/* Initialize the chip
Arguments: None
Returns : None
*/
void MPU9255::init()
{
  Wire.begin();// enable I2C interface
  Hreset();
  write(MPU_address,CONFIG, 0x03); // set DLPF_CFG to 11
  write(MPU_address,SMPLRT_DIV, 0x00);// set prescaler sample rate to 0
  write(MPU_address,GYRO_CONFIG, 0x01);// set gyro to 3.6 KHz bandwidth, and 0.11 ms using FCHOICE bits
  write(MPU_address,INT_PIN_CFG, 0x02);// BYPASS ENABLE (Necessary for the magnetometer to function)
  write(MAG_address, CNTL, 0x16);//set magnetometer to read in mode 2 and enable 16 bit measurements

  ///read magnetometer sensitivity for compensation
  mx_sensitivity = (((read(MAG_address, ASAX)-128)*0.5)/128)+1;
  my_sensitivity = (((read(MAG_address, ASAY)-128)*0.5)/128)+1;
  mz_sensitivity = (((read(MAG_address, ASAZ)-128)*0.5)/128)+1;

  ///read base offset from the accelerometer and the gyroscope
  AX_offset = uint8ToUint16(read(MPU_address,XA_OFFSET_L), read(MPU_address,XA_OFFSET_H));
  AY_offset = uint8ToUint16(read(MPU_address,YA_OFFSET_L), read(MPU_address,YA_OFFSET_H));
  AZ_offset = uint8ToUint16(read(MPU_address,ZA_OFFSET_L), read(MPU_address,ZA_OFFSET_H));

  GX_offset = uint8ToUint16(read(MPU_address,XG_OFFSET_L), read(MPU_address,XG_OFFSET_H));
  GY_offset = uint8ToUint16(read(MPU_address,YG_OFFSET_L), read(MPU_address,YG_OFFSET_H));
  GZ_offset = uint8ToUint16(read(MPU_address,ZG_OFFSET_L), read(MPU_address,ZG_OFFSET_H));
}

void MPU9255::set_gyro_offset(axis selected_axis, int16_t offset)
{
  switch(selected_axis)
  {
    case X_axis:
      offset = offset + GX_offset;
      write(MPU_address,XG_OFFSET_L,(offset & 0x00FF));
      write(MPU_address,XG_OFFSET_H,(offset>>8));
      break;

    case Y_axis:
      offset = offset + GY_offset;
      write(MPU_address,YG_OFFSET_L,(offset & 0x00FF));
      write(MPU_address,YG_OFFSET_H,(offset>>8));
      break;

    case Z_axis:
      offset = offset + GZ_offset;
      write(MPU_address,ZG_OFFSET_L,(offset & 0x00FF));
      write(MPU_address,ZG_OFFSET_H,(offset>>8));
      break;
  }
}

void MPU9255::set_acc_offset(axis selected_axis, int16_t offset)
{
  switch(selected_axis)
  {
    case X_axis:
      offset = offset + AX_offset;
      write(MPU_address,XA_OFFSET_L,(offset & 0x00FF));
      write(MPU_address,XA_OFFSET_H,(offset>>8));
      break;

    case Y_axis:
      offset = offset + AY_offset;
      write(MPU_address,YA_OFFSET_L,(offset & 0x00FF));
      write(MPU_address,YA_OFFSET_H,(offset>>8));
      break;

    case Z_axis:
      offset = offset + AZ_offset;
      write(MPU_address,ZA_OFFSET_L,(offset & 0x00FF));
      write(MPU_address,ZA_OFFSET_H,(offset>>8));
      break;
  }
}

void MPU9255::set_acc_bandwidth(bandwidth selected_bandwidth)
{
  switch(selected_bandwidth)
  {
    case acc_1113Hz:
      write_OR(MPU_address,ACCEL_CONFIG_2,(1<<3));//set accel_fchoice_b to 1
      break;

    case acc_460Hz:
      //set accel_fchoice_b to 0 and  A_DLPF_CFG to 0(000)
      write_AND(MPU_address,ACCEL_CONFIG_2,~((1<<3)|(1<<2)|(1<<1)|(1<<0)));
      break;

    case acc_184Hz:
      write_AND(MPU_address,ACCEL_CONFIG_2,~(1<<3));//set accel_fchoice_b to 0
      //set A_DLPF_CFG to 1(001)
      write_AND(MPU_address,ACCEL_CONFIG_2,~((1<<1)|(1<<2)));
      write_OR(MPU_address,ACCEL_CONFIG_2,(1<<0));
      break;

    case acc_92Hz:
      write_AND(MPU_address,ACCEL_CONFIG_2,~(1<<3));//set accel_fchoice_b to 0
      //set A_DLPF_CFG to 2(010)
      write_AND(MPU_address,ACCEL_CONFIG_2,~((1<<0)|(1<<2)));
      write_OR(MPU_address,ACCEL_CONFIG_2,(1<<1));
      break;

    case acc_41Hz:
      write_AND(MPU_address,ACCEL_CONFIG_2,~(1<<3));//set accel_fchoice_b to 0
      //set A_DLPF_CFG to 3(011)
      write_AND(MPU_address,ACCEL_CONFIG_2,~(1<<2));
      write_OR(MPU_address,ACCEL_CONFIG_2,(1<<0)|(1<<1));
      break;

    case acc_20Hz:
      write_AND(MPU_address,ACCEL_CONFIG_2,~(1<<3));//set accel_fchoice_b to 0
      //set A_DLPF_CFG to 4(100)
      write_AND(MPU_address,ACCEL_CONFIG_2,~((1<<0)|(1<<1)));
      write_OR(MPU_address,ACCEL_CONFIG_2,(1<<2));
      break;

    case acc_10Hz:
      write_AND(MPU_address,ACCEL_CONFIG_2,~(1<<3));//set accel_fchoice_b to 0
      //set A_DLPF_CFG to 5(101)
      write_AND(MPU_address,ACCEL_CONFIG_2,~(1<<1));
      write_OR(MPU_address,ACCEL_CONFIG_2,(1<<0)|(1<<2));
      break;

    case acc_5Hz:
      write_AND(MPU_address,ACCEL_CONFIG_2,~(1<<3));//set accel_fchoice_b to 0
      //set A_DLPF_CFG to 6(110)
      write_AND(MPU_address,ACCEL_CONFIG_2,~(1<<0));
      write_OR(MPU_address,ACCEL_CONFIG_2,(1<<1)|(1<<2));
      break;
  }
}

void MPU9255::set_gyro_bandwidth(bandwidth selected_bandwidth)
{
  switch(selected_bandwidth)
  {
    case gyro_8800Hz:
      write_OR(MPU_address,GYRO_CONFIG,(1<<0));//set Fchoice_b <0> to 1
      break;

    case gyro_3600Hz:
      write_AND(MPU_address,GYRO_CONFIG,~(1<<0));//set Fchoice_b <0> to 0
      write_OR(MPU_address,GYRO_CONFIG,(1<<1));//set Fchoice_b <1> to 1
      break;

    case gyro_250Hz:
      write_AND(MPU_address,GYRO_CONFIG,~((1<<0)|(1<<1)));//set both Fchoice_b to 0
      //write 0 to DLPF_CFG(000)
      write_AND(MPU_address,CONFIG,~((1<<0)|(1<<1)|(1<<2)));
      break;

    case gyro_184Hz:
      write_AND(MPU_address,GYRO_CONFIG,~((1<<0)|(1<<1)));//set both Fchoice_b to 0
      //write 1 to thew DLPF_CFG(001)
      write_AND(MPU_address,CONFIG,~((1<<1)|(1<<2)));
      write_OR(MPU_address,CONFIG,(1<<0));
      break;

    case gyro_92Hz:
      write_AND(MPU_address,GYRO_CONFIG,~((1<<0)|(1<<1)));//set both Fchoice_b to 0
      //write 2 to thew DLPF_CFG(010)
      write_AND(MPU_address,CONFIG,~((1<<2)|(1<<0)));
      write_OR(MPU_address,CONFIG,(1<<1));
      break;

    case gyro_41Hz:
      write_AND(MPU_address,GYRO_CONFIG,~((1<<0)|(1<<1)));//set both Fchoice_b to 0
      //write 3 to thew DLPF_CFG(011)
      write_AND(MPU_address,CONFIG,~(1<<2));
      write_OR(MPU_address,CONFIG,(1<<0)|(1<<1));
      break;

    case gyro_20Hz:
      write_AND(MPU_address,GYRO_CONFIG,~((1<<0)|(1<<1)));//set both Fchoice_b to 0
      //write 4 to thew DLPF_CFG(100)
      write_AND(MPU_address,CONFIG,~((1<<1)|(1<<0)));
      write_OR(MPU_address,CONFIG,(1<<2));
      break;

    case gyro_10Hz:
      write_AND(MPU_address,GYRO_CONFIG,~((1<<0)|(1<<1)));//set both Fchoice_b to 0
      //write 5 to thew DLPF_CFG(101)
      write_AND(MPU_address,CONFIG,~(1<<1));
      write_OR(MPU_address,CONFIG,(1<<2)|(1<<0));
      break;

    case gyro_5Hz:
      write_AND(MPU_address,GYRO_CONFIG,~((1<<0)|(1<<1)));//set both Fchoice_b to 0
      //write 6 to thew DLPF_CFG(110)
      write_AND(MPU_address,CONFIG,~(1<<0));
      write_OR(MPU_address,CONFIG,(1<<1)|(1<<2));
      break;
  }
}

uint8_t MPU9255::getScale(uint8_t current_state, scales selected_scale)
{
  if(selected_scale == scale_2g || selected_scale == scale_250dps)
  {
    current_state &= ~((1<<3)|(1<<4));
  }

  if(selected_scale == scale_4g || selected_scale == scale_500dps)
  {
    current_state &= ~(1<<4);
    current_state |= (1<<3);
  }

  if(selected_scale == scale_8g || selected_scale == scale_1000dps)
  {
    current_state &= ~(1<<3);
    current_state |= (1<<4);
  }

  if(selected_scale == scale_16g || selected_scale == scale_2000dps)
  {
    current_state |= (1<<4)|(1<<3);
  }

  return current_state;
}

/* Set accelerometer scale
Arguments:
- Selected scale
Returns : None
*/
void MPU9255::set_acc_scale(scales selected_scale)
{
	uint8_t val = read(MPU_address,ACCEL_CONFIG);//read old register value
  	val = getScale(val,selected_scale);
	write(MPU_address,ACCEL_CONFIG,val);// commit changes
}

/* Set gyroscope scale
Arguments:
- Selected scale
Returns : None
*/
void MPU9255::set_gyro_scale(scales selected_scale)
{
	uint8_t val=read(MPU_address,GYRO_CONFIG);//read old register value
  	val = getScale(val,selected_scale);
	write(MPU_address,GYRO_CONFIG,val);// commit changes
}
