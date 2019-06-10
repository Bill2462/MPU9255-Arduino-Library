/*
Scale example
This example shows how to set different accelerometer/gyroscope scales.
*/

#include <MPU9255.h>//include MPU9255 library

MPU9255 mpu;

void print_data()//take some raw readings and print them in serial monitor
{
	for(int i=0;i<=10;i++)
	{
		mpu.read_acc();
		mpu.read_gyro();

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
		Serial.println(mpu.gz);
		delay(1000);
	}
}


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
	//set gyroscope scale to +- 250 dps and accelerometer scale to +- 2g
	Serial.println("Gyro scale : +- 250 dps");
	Serial.println("Acc scale  : +- 2g");
	mpu.set_acc_scale(scale_2g);//set accelerometer scale
	mpu.set_gyro_scale(scale_250dps);//set gyroscope scale
	print_data();//print some data
	Serial.println("");

	//set gyroscope scale to +- 500 dps and accelerometer scale to +- 4g
	Serial.println("Gyro scale : +- 500 dps");
	Serial.println("Acc scale  : +- 4g");
	mpu.set_acc_scale(scale_4g);
	mpu.set_gyro_scale(scale_500dps);
	print_data();
	Serial.println("");

	//set gyroscope scale to +- 1000 dps and accelerometer scale to +- 8g
	Serial.println("Gyro scale : +- 1000 dps");
	Serial.println("Acc scale  : +- 8g");
	mpu.set_acc_scale(scale_8g);
	mpu.set_gyro_scale(scale_1000dps);
	print_data();
	Serial.println("");

	//set gyroscope scale to +- 2000 dps and accelerometer scale to +- 16g
	Serial.println("Gyro scale : +- 2000 dps");
	Serial.println("Acc scale  : +- 16g");
	mpu.set_acc_scale(scale_16g);
	mpu.set_gyro_scale(scale_2000dps);
	print_data();
	Serial.println("");
}
