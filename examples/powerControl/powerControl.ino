/*
power control example
This example disables and reenables all modules that can be disabled.
*/

#include <MPU9255.h>//include MPU9255 library

MPU9255 mpu;

void print_data()//read and print raw data from the sensors
{
	for(int i=0;i<=10;i++)
	{
		mpu.read_acc();
		mpu.read_gyro();
		mpu.read_mag();

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
		delay(500);
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
  Serial.println("Taking some control measurements...");
  print_data();//print some data
	Serial.println();

	////////// disable modules one by one //////////

	//disable magnetometer
	Serial.println("Disabling magnetometer...");
	mpu.disable(magnetometer);//disable module
	print_data();
	Serial.println();

	//disable accelerometer X axis
	Serial.println("Disabling accelerometer X axis...");
	mpu.disable(Acc_X);
	print_data();
	Serial.println();

	//disable accelerometer Y axis
	Serial.println("Disabling accelerometer Y axis...");
	mpu.disable(Acc_Y);
	print_data();
	Serial.println();

	//disable accelerometer Z axis
	Serial.println("Disabling accelerometer Z axis...");
	mpu.disable(Acc_Z);
	print_data();
	Serial.println();

	//disable gyroscope X axis
	Serial.println("Disabling gyroscope X axis...");
	mpu.disable(Gyro_X);
	print_data();
	Serial.println();

	//disable gyroscope Y axis
	Serial.println("Disabling  gyroscope Y axis...");
	mpu.disable(Gyro_Y);
	print_data();
	Serial.println();

	//disable gyroscope Z axis
	Serial.println("Disabling gyroscope Z axis...");
	mpu.disable(Gyro_Z);
	print_data();
	Serial.println();

	////////// Re-enable all modules //////////

	//enable magnetometer
	Serial.println("Enabling magnetometer...");
	mpu.enable(magnetometer);//enable module
	print_data();
	Serial.println();

	//enable accelerometer X axis
	Serial.println("Enabling accelerometer X axis...");
	mpu.enable(Acc_X);
	print_data();
	Serial.println();

	//enable accelerometer Y axis
	Serial.println("Enabling accelerometer Y axis...");
	mpu.enable(Acc_Y);
	print_data();
	Serial.println();

	//enable accelerometer Z axis
	Serial.println("Enabling accelerometer Z axis...");
	mpu.enable(Acc_Z);
	print_data();
	Serial.println();

	//enable gyroscope X axis
	Serial.println("Enabling gyroscope X axis...");
	mpu.enable(Gyro_X);
	print_data();
	Serial.println();

	//enable gyroscope Y axis
	Serial.println("Enabling  gyroscope Y axis...");
	mpu.enable(Gyro_Y);
	print_data();
	Serial.println();

	//enable gyroscope Z axis
	Serial.println("Enabling gyroscope Z axis...");
	mpu.enable(Gyro_Z);
	print_data();
	Serial.println();
}
