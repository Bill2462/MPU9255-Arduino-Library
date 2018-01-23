/*
Example 1 :
This example initializes the sensors and outputs raw data from Gyroscope, Accelerometer and Magnetometer.

*/

#include <MPU9255.h>// include MPU9255 library

MPU9255 mpu;

void setup() {
  Serial.begin(115200);// initialize Serial port
  mpu.init();// Initialize MPU9255 chip
}

void loop() {
  mpu.read_acc();// read data from accelerometer
  mpu.read_gyro();// get data from gyroscope
  mpu.read_mag();// get data from the magnetometer

  // print all data in serial monitor
  Serial.print("AX: ");
  Serial.print(mpu.ax);
  Serial.print(" AY: ");
  Serial.print(mpu.ay);
  Serial.print(" AZ: ");
  Serial.print(mpu.az);// accelerometer data
  Serial.print("  GX: ");
  Serial.print(mpu.gx);
  Serial.print(" GY: ");
  Serial.print(mpu.gy);
  Serial.print(" GZ: ");
  Serial.print(mpu.gz);// gyroscope data
  Serial.print("  MX: ");
  Serial.print(mpu.mx);
  Serial.print(" MY: ");
  Serial.print(mpu.my);
  Serial.print(" MZ: ");
  Serial.println(mpu.mz);// gyroscope data
  delay(100);
}
