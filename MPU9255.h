/*
Copyright (C) Bill2462 from https://github.com/Bill2462
 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 3 as published by the Free Software Foundation.
*/

#ifndef MPU9255_H
#define MPU9255_H

#include <Arduino.h>
#include <Wire.h>

//sensor adresses
#define MAG_adress 0x0C//magnetometer
#define MPU_adress 0x68//main chip

//main chip
#define USER_CTRL  0x6A
#define PWR_MGMT_1 0x6B
#define PWR_MGMT_2 0x6C
#define SIGNAL_PATH_RESET 0x68
#define INT_PIN_CFG 0x37
#define ST1 0x02
#define ACCEL_CONFIG 0x1C
#define GYRO_CONFIG 0x1B
#define CONFIG 0x1A
#define SMPLRT_DIV 0x19
#define INT_ENABLE 0x38

//magnetometer
#define CNTL 0x0A
#define CNTL2 0x0B

/// data registers
#define MAG_XOUT_L 0x03//magnetometer
#define GYRO_XOUT_H 0x43//gyro
#define ACCEL_XOUT_H 0x3B//accelerometer
#define TEMP_OUT_H 0x41//thermometer

class MPU9255
{
public:

//acceleration data
int16_t ax=0;//X axis
int16_t ay=0;//Y axis
int16_t az=0;//Z axis

//gyroscope data
int16_t gx=0;//X axis
int16_t gy=0;//Y axis
int16_t gz=0;//Z axis

//magnetometer data
int16_t mx=0;//X axis
int16_t my=0;//Y axis
int16_t mz=0;//Z axis

//general control
void init();//Initialize magnetometer and IMU
void set_acc_scale(unsigned char value);//Set accelerometer scale
void set_gyro_scale(unsigned char value);//Set gyroscope scale

//reset
void Hreset();//Hard reset - Resets entire chip (call of init function is required to use chip afterwards)
void gyro_RST();//reset gyroscope signal patch (registers values are preserved)
void acc_RST();//reset accelerometer signal patch (registers values are preserved)
void temp_RST();//reset termometer signal patch (registers values are preserved)
void SIG_COND_RST();//reset all signal patchs and sensor registers in accelerometer gyroscope and termometer
void mag_SoftRST();//reset Magnetometer

//data read function
void read_acc();//read data from accelerometer
void read_gyro();//read data from gyroscope
void read_mag();//read data from magnetometer
int16_t read_temp();//read temperature from the internal sensor (EXPERIMENTAL!)

//power control
void mag_PWRD();//magnetometer powerdown
void mag_PWRU();//magnetometer powerup
void sleep_enable();//put main chip in sleep mode
void sleep_disable();//disable sleep mode
void disable_ax();//disable accelerometer X axis
void disable_ay();//disable accelerometer Y axis
void disable_az();//disable accelerometer Z axis
void disable_gx();//disable gyroscope X axis
void disable_gy();//disable gyroscope Y axis
void disable_gz();//disable gyroscope Z axis
void enable_ax();//enable accelerometer X axis
void enable_ay();//enable accelerometer Y axis
void enable_az();//enable accelerometer Z axis
void enable_gx();//enable gyroscope X axis
void enable_gy();//enable gyroscope Y axis
void enable_gz();//enable gyroscope Z axis


private:
uint8_t read(uint8_t address, uint8_t subAddress);//read one byte from register
void write(uint8_t address, uint8_t subAddress, uint8_t data);//write one byte of data to the register
void write_OR(uint8_t address, uint8_t subAddress, uint8_t data);//write one byte of data to the register (with OR operation)
void write_AND(uint8_t address, uint8_t subAddress, uint8_t data);//write one byte of data to the register (with AND operation)
};

#endif
