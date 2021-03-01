/**
 * @file MPU9255.cpp
 * @brief This source file contains methods for initialising MPU9255.
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
 * @brief Initialise MPU9255 module.
 * @return 0 if success, 1 if imu or magnetometer fails
 */
uint8_t MPU9255::init()
{
  Wire.begin();//enable I2C interface
  Hreset();//reset the chip
  write(MPU_address,CONFIG, 0x03);//set DLPF_CFG to 0b11
  write(MPU_address,SMPLRT_DIV, 0x00);//set prescaler sample rate to 0
  write(MPU_address,GYRO_CONFIG, 0x02);//set gyro to 3.6 kHz bandwidth, and 0.11 ms using FCHOICE_B=0b10 (i.e. FCHOICE=0b01)
  write(MPU_address,INT_PIN_CFG, 0x02);//enable bypass
  write(MAG_address, CNTL, 0x16);//set magnetometer to read in mode 2 and enable 16 bit measurements

  //read magnetometer sensitivity
  mx_sensitivity = (((read(MAG_address, ASAX)-128)*0.5)/128)+1;
  my_sensitivity = (((read(MAG_address, ASAY)-128)*0.5)/128)+1;
  mz_sensitivity = (((read(MAG_address, ASAZ)-128)*0.5)/128)+1;

  //read factory gyroscope offset
  GX_offset = ((int16_t)read(MPU_address, XG_OFFSET_H) << 8) | read(MPU_address, XG_OFFSET_L);
  GY_offset = ((int16_t)read(MPU_address, YG_OFFSET_H) << 8) | read(MPU_address, YG_OFFSET_L);
  GZ_offset = ((int16_t)read(MPU_address, XG_OFFSET_H) << 8) | read(MPU_address, ZG_OFFSET_L);

  //Based on http://www.digikey.com/en/pdf/i/invensense/mpu-hardware-offset-registers .
  //read factory accelerometer offset

  //read the register values and save them as a 16 bit value
  AX_offset = (read(MPU_address,XA_OFFSET_H)<<8) | (read(MPU_address,XA_OFFSET_L));
  AY_offset = (read(MPU_address,YA_OFFSET_H)<<8) | (read(MPU_address,YA_OFFSET_L));
  AZ_offset = (read(MPU_address,ZA_OFFSET_H)<<8) | (read(MPU_address,ZA_OFFSET_L));
  
  //shift offset values to the right to remove the LSB
  AX_offset = AX_offset>>1;
  AY_offset = AY_offset>>1;
  AZ_offset = AZ_offset>>1;

  return (testIMU() || testMag());// return the output
}

/**
 * @brief Set gyroscope offset.
 * @param selected_axis Axis for which we want to set the offset.
 * @param offset Offset.
 */
void MPU9255::set_gyro_offset(axis selected_axis, int16_t offset)
{
  switch(selected_axis)
  {
    case X_axis:
      offset = offset + GX_offset;//add offset to the factory offset
      write(MPU_address,XG_OFFSET_L,(offset & 0xFF));//write low byte
      write(MPU_address,XG_OFFSET_H,(offset>>8));//write high byte
      break;

    case Y_axis:
      offset = offset + GY_offset;
      write(MPU_address,YG_OFFSET_L,(offset & 0xFF));
      write(MPU_address,YG_OFFSET_H,(offset>>8));
      break;

    case Z_axis:
      offset = offset + GZ_offset;
      write(MPU_address,ZG_OFFSET_L,(offset & 0xFF));
      write(MPU_address,ZG_OFFSET_H,(offset>>8));
      break;
  }
}

/**
 * @brief Set accelerometer offset.
 * @param selected_axis Selected axis.
 * @param offset Offset.
 */
void MPU9255::set_acc_offset(axis selected_axis, int16_t offset)
{

  switch(selected_axis)
  {
    case X_axis:
      offset = offset + AX_offset;//add offset to the factory offset
      write(MPU_address,XA_OFFSET_L,(offset & 0xFF)<<1);//write low byte
      write(MPU_address,XA_OFFSET_H,(offset>>7));//write high byte
      break;

    case Y_axis:
      offset = offset + AY_offset;
      write(MPU_address,YA_OFFSET_L,(offset & 0xFF)<<1);
      write(MPU_address,YA_OFFSET_H,(offset>>7));
      break;

    case Z_axis:
      offset = offset + AZ_offset;
      write(MPU_address,ZA_OFFSET_L,(offset & 0xFF)<<1);
      write(MPU_address,ZA_OFFSET_H,(offset>>7));
      break;
  }
}

/**
 * @brief Set accelerometer bandwidth.
 * @param selected_bandwidth Accelerometer bandwidth.
 */
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

/**
 * @brief Set gyroscope bandwidth.
 * @param selected_bandwidth Gyroscope bandwidth.
 */
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
      //write 0(000) to DLPF_CFG
      write_AND(MPU_address,CONFIG,~((1<<0)|(1<<1)|(1<<2)));
      break;

    case gyro_184Hz:
      write_AND(MPU_address,GYRO_CONFIG,~((1<<0)|(1<<1)));//set both Fchoice_b to 0
      //write 1(001) to DLPF_CFG
      write_AND(MPU_address,CONFIG,~((1<<1)|(1<<2)));
      write_OR(MPU_address,CONFIG,(1<<0));
      break;

    case gyro_92Hz:
      write_AND(MPU_address,GYRO_CONFIG,~((1<<0)|(1<<1)));//set both Fchoice_b to 0
      //write 2(010) to DLPF_CFG
      write_AND(MPU_address,CONFIG,~((1<<2)|(1<<0)));
      write_OR(MPU_address,CONFIG,(1<<1));
      break;

    case gyro_41Hz:
      write_AND(MPU_address,GYRO_CONFIG,~((1<<0)|(1<<1)));//set both Fchoice_b to 0
      //write 3(011) to DLPF_CFG
      write_AND(MPU_address,CONFIG,~(1<<2));
      write_OR(MPU_address,CONFIG,(1<<0)|(1<<1));
      break;

    case gyro_20Hz:
      write_AND(MPU_address,GYRO_CONFIG,~((1<<0)|(1<<1)));//set both Fchoice_b to 0
      //write 4(100) to DLPF_CFG
      write_AND(MPU_address,CONFIG,~((1<<1)|(1<<0)));
      write_OR(MPU_address,CONFIG,(1<<2));
      break;

    case gyro_10Hz:
      write_AND(MPU_address,GYRO_CONFIG,~((1<<0)|(1<<1)));//set both Fchoice_b to 0
      //write 5(101) to DLPF_CFG
      write_AND(MPU_address,CONFIG,~(1<<1));
      write_OR(MPU_address,CONFIG,(1<<2)|(1<<0));
      break;

    case gyro_5Hz:
      write_AND(MPU_address,GYRO_CONFIG,~((1<<0)|(1<<1)));//set both Fchoice_b to 0
      //write 6(110) to DLPF_CFG
      write_AND(MPU_address,CONFIG,~(1<<0));
      write_OR(MPU_address,CONFIG,(1<<1)|(1<<2));
      break;
  }
}

/**
 * @brief Convert selected scale to to register value.
 * @details Function that takes the current value of the ACC control register
 * and applies the selected scale.
 * @param current_state Current state of the ACC control register.
 * @param selected_scale Selected scale.
 * @return New register state.
 */
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

/**
 * @brief Set accelerometer scale.
 * @param selected_scale Selected scale.
 */
void MPU9255::set_acc_scale(scales selected_scale)
{
  uint8_t val = read(MPU_address,ACCEL_CONFIG);//read old register value
  val = getScale(val,selected_scale);//get new register value
  write(MPU_address,ACCEL_CONFIG,val);//commit changes
}

/**
 * @brief Set gyroscope scale.
 * @param selected_scale Selected scale.
 */
void MPU9255::set_gyro_scale(scales selected_scale)
{
  uint8_t val=read(MPU_address,GYRO_CONFIG);
  val = getScale(val,selected_scale);
  write(MPU_address,GYRO_CONFIG,val);
}

/**
 * @brief Test if IMU (gyroscope and accelerometer) is working.
 * @return 0 if IMU is working and 1 otherwise.
 */
uint8_t MPU9255::testIMU()
{
  if(read(MPU_address,WHO_AM_I)==0xFF)
  {
    return 1;
  }
  return 0;
}

/**
 * @brief Test if magnetometer is working.
 * @return 0 if magnetmeter is working and 1 otherwise.
 */
uint8_t MPU9255::testMag()
{
  if(read(MAG_address,MAG_ID)==0xFF)
  {
    return 1;
  }
  return 0;
}
