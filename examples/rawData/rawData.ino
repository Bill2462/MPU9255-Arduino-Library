/*
Example 1 : 
This example initializes the sensors and outputs raw data from Gyroscope, Accelerometer and Magnetometer. 

*/

#include <Wire.h>// include MPU9255 library
#include <MPU9255.h>// include MPU9255 library

MPU9255 mpu;

void setup() {
  Wire.begin();//initialize I2C interface
  Serial.begin(115200);// initialize Serial port 
  mpu.init();// Initialize MPU9255 chip
}

void loop() {
  mpu.read_acc();// read data from accelerometer
  int ax=mpu.get_ax();// read acceleration in X axis
  int ay=mpu.get_ay();// read acceleration in Y axis
  int az=mpu.get_az();// read acceleration in Z axis
  
  mpu.read_gyro();// get data from gyroscope
  int gx=mpu.get_gx();// read rotation in X axis
  int gy=mpu.get_gy();// read rotation in Y axis
  int gz=mpu.get_gz();// read rotation in Z axis
  
  mpu.read_mag();// get data from the magnetometer 
  int mx=mpu.get_mx();// return magnetic field data from X axis 
  int my=mpu.get_my();// return magnetic field data from Y axis 
  int mz=mpu.get_mz();// return magnetic field data from Z axis 
  // print all data in serial monitor
  Serial.print("AX: "); Serial.print(ax); Serial.print(" AY: "); Serial.print(ay); Serial.print(" AZ: "); Serial.print(az);// accelerometer data 
  Serial.print("  GX: "); Serial.print(gx); Serial.print(" GY: "); Serial.print(gy); Serial.print(" GZ: "); Serial.print(gz);// gyroscope data
  Serial.print("  MX: "); Serial.print(mx); Serial.print(" MY: "); Serial.print(my); Serial.print(" MZ: "); Serial.println(mz);// gyroscope data
  delay(100);
}
