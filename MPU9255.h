/*
Copyright (C) Bill2462 from https://github.com/Bill2462 
 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.

*/

#ifndef MPU9255_H
#define MPU9255_H
 
#include <Arduino.h>
#include <Wire.h> 

//############################################# Definitions ############################################# 

// definitions of sensors adresses 
#define MAG_adress 0x0C// magnetometer 
#define MPU_adress 0x68// main chip adress

// registers adresses 

//control registers 
#define USER_CTRL  0x6A
#define PWR_MGMT_2 0x6B
#define INT_PIN_CFG 0x37
#define ST1 0x02
#define ST2 0x09
#define CNTL 0x0A
#define ACCEL_CONFIG 0x1C
#define GYRO_CONFIG 0x1B
#define CONFIG 0x1A
#define SMPLRT_DIV 0x19
#define GYRO_CONFIG 0x1B
#define ACCEL_CONFIG 0x1C
#define INT_PIN_CFG 0x37
#define INT_ENABLE 0x38

// data registers 

// magnetometer 
#define MAG_XOUT_L 0x03
#define MAG_XOUT_H 0x04
#define MAG_YOUT_L 0x05
#define MAG_YOUT_H 0x06
#define MAG_ZOUT_L 0x07
#define MAG_ZOUT_H 0x08

// gyroscope
#define GYRO_XOUT_H 0x43
#define GYRO_XOUT_L 0x44
#define GYRO_YOUT_H 0x45
#define GYRO_YOUT_L 0x46
#define GYRO_ZOUT_H 0x47
#define GYRO_ZOUT_L 0x48

//accelerometer 
#define ACCEL_XOUT_H 0x3B
#define ACCEL_XOUT_L 0x3C
#define ACCEL_YOUT_H 0x3D
#define ACCEL_YOUT_L 0x3E
#define ACCEL_ZOUT_H 0x3F
#define ACCEL_ZOUT_L 0x40

//############################################# MPU9255 class ################################################

class MPU9255 
{

public:

void init();
// ---- Data read functions ----- 
void read_acc();
int16_t get_ax();
int16_t get_ay();
int16_t get_az();

void read_gyro();
int16_t get_gx();
int16_t get_gy();
int16_t get_gz();

void read_mag();
int16_t get_mx();
int16_t get_my();
int16_t get_mz();
 
private:
uint8_t read(uint8_t address, uint8_t subAddress);
void write(uint8_t address, uint8_t subAddress, uint8_t data);

};

#endif
