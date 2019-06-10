/*
Raw data example
This example reads raw readings from the magnetometer gyroscope and the accelerometer and then
displays them in serial monitor.
*/

#include <MPU9255.h>//include MPU9255 library

MPU9255 mpu;

void setup() {
  Serial.begin(115200);//initialize Serial port

  if(mpu.init())
  {
  Serial.println("initialization failed");
  }
  else
  {
  Serial.println("initialization successful!");
  }

}

void loop() {
  mpu.read_acc();//get data from the accelerometer
  mpu.read_gyro();//get data from the gyroscope
  mpu.read_mag();//get data from the magnetometer

  //print all data in serial monitor
  Serial.print("AX: ");
  Serial.print(mpu.ax);
  Serial.print(" AY: ");
  Serial.print(mpu.ay);
  Serial.print(" AZ: ");
  Serial.print(mpu.az);
  Serial.print("    GX: ");
  Serial.print(mpu.gx);
  Serial.print(" GY: ");
  Serial.print(mpu.gy);
  Serial.print(" GZ: ");
  Serial.print(mpu.gz);
  Serial.print("    MX: ");
  Serial.print(mpu.mx);
  Serial.print(" MY: ");
  Serial.print(mpu.my);
  Serial.print(" MZ: ");
  Serial.println(mpu.mz);
  delay(100);
}
