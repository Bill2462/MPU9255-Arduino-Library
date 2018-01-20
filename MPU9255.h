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
#define MPU_adress 0x68//gyroscope and accelerometer

//control registers
#define USER_CTRL  0x6A
#define PWR_MGMT_2 0x6B
#define INT_PIN_CFG 0x37
#define ST1 0x02
#define CNTL 0x0A
#define ACCEL_CONFIG 0x1C
#define GYRO_CONFIG 0x1B
#define CONFIG 0x1A
#define SMPLRT_DIV 0x19
#define GYRO_CONFIG 0x1B
#define ACCEL_CONFIG 0x1C
#define INT_PIN_CFG 0x37
#define INT_ENABLE 0x38

/// data registers
#define MAG_XOUT_L 0x03//magnetometer
#define GYRO_XOUT_H 0x43//gyro
#define ACCEL_XOUT_H 0x3B//accelerometer

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

void init();//Initialize magnetometer and IMU
void set_acc_scale(unsigned char value);//Set accelerometer scale
void set_gyro_scale(unsigned char value);//Set gyroscope scale
void read_acc();//read data from accelerometer
void read_gyro();//read data from gyroscope
void read_mag();//read data from magnetometer

private:
uint8_t read(uint8_t address, uint8_t subAddress);//read one byte from register
void write(uint8_t address, uint8_t subAddress, uint8_t data);//write one byte of data to the register

};

#endif
