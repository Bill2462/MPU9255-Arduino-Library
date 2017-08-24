/*
Example 3 : 
This example reads data from the gyroscope and the accelerometer in 4 different scales. 
*/

#include <Wire.h>// include MPU9255 library
#include <MPU9255.h>// include MPU9255 library

MPU9255 mpu;

void print_data()// read and print all data 
{
	mpu.read_acc();
	mpu.read_gyro();

	Serial.print("AX: "); 
	Serial.print(mpu.ax); 
	Serial.print(" AY: "); 
	Serial.print(mpu.ay); 
	Serial.print(" AZ: "); 
	Serial.print(mpu.az);
	Serial.print("     GX: "); 
	Serial.print(mpu.gx); 
	Serial.print(" GY: "); 
	Serial.print(mpu.gy); 
	Serial.print(" GZ: "); 
	Serial.println(mpu.gz);
}


void setup() {
  Wire.begin();//initialize I2C interface
  Serial.begin(115200);// initialize Serial port 
  mpu.init();// Initialize MPU9255 chip
}

void loop() {
Serial.println("Gyro scale : +- 250 dps");
Serial.println("Acc scale  : +- 2g");
// set gyroscope scale to +- 250 dps and accelerometer scale to +- 2g
mpu.set_acc_scale(1);
mpu.set_gyro_scale(1);
for(int i=0;i<=10;i++)//make some readings 
{
print_data();
delay(1000);
}

Serial.println("Gyro scale : +- 500 dps");
Serial.println("Acc scale  : +- 4g");
// set gyroscope scale to +- 500 dps and accelerometer scale to +- 4g
mpu.set_acc_scale(2);
mpu.set_gyro_scale(2);
for(int i=0;i<=10;i++)//make some readings 
{
print_data();
delay(1000);
}

Serial.println("Gyro scale : +- 1000 dps");
Serial.println("Acc scale  : +- 8g");
// set gyroscope scale to +- 1000 dps and accelerometer scale to +- 8g
mpu.set_acc_scale(3);
mpu.set_gyro_scale(3);
for(int i=0;i<=10;i++)//make some readings 
{
print_data();
delay(1000);
}

Serial.println("Gyro scale : +- 2000 dps");
Serial.println("Acc scale  : +- 16g");
// set gyroscope scale to +- 2000 dps and accelerometer scale to +- 16g
mpu.set_acc_scale(4);
mpu.set_gyro_scale(4);
for(int i=0;i<=10;i++)//make some readings 
{
print_data();
delay(1000);
}
}
