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
//#define ST2 0x09
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

// gyroscope
#define GYRO_XOUT_H 0x43

//accelerometer 
#define ACCEL_XOUT_H 0x3B

//############################################# MPU9255 class ################################################

class MPU9255 
{

public:
 // ---- Variabled ----
int16_t ax=0;
int16_t ay=0;
int16_t az=0;

int16_t gx=0;
int16_t gy=0;
int16_t gz=0;

int16_t mx=0;
int16_t my=0;
int16_t mz=0;
 
// ---- General functions ----- 
void init();
void set_acc_scale(unsigned char value);
void set_gyro_scale(unsigned char value);
 
// ---- Data read functions ----- 
void read_acc();
void read_gyro();
void read_mag();
 
private:
uint8_t read(uint8_t address, uint8_t subAddress);
void write(uint8_t address, uint8_t subAddress, uint8_t data);

};

#endif
