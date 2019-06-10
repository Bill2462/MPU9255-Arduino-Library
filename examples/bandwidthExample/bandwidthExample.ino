/*
Bandwidth example
This example shows how different low-pass filter settings are affecting the readings from the
accelerometer and the gyroscope.
*/

#include <MPU9255.h>//include MPU9255 library

MPU9255 mpu;

void print_data()//take some raw readings and print them in serial monitor
{
  for(int i=0;i<=500;i++)
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
    delay(10);
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
  //set gyroscope bandwidth to 8800Hz and accelerometer bandwidth to 1113Hz
  Serial.println("Gyro bandwidth : 8800Hz");
  Serial.println("Acc bandwidth  : 1113Hz");
  delay(4000);
  mpu.set_acc_bandwidth(acc_1113Hz);//set accelerometer bandwidth
  mpu.set_gyro_bandwidth(gyro_8800Hz);//set gyroscope bandwidth
  print_data();//print some data
  Serial.println("");

  //set gyroscope bandwidth to 250Hz and accelerometer bandwidth to 184Hz
  Serial.println("Gyro bandwidth : 250Hz");
  Serial.println("Acc bandwidth  : 184Hz");
  delay(4000);
  mpu.set_acc_bandwidth(acc_184Hz);//set accelerometer bandwidth
  mpu.set_gyro_bandwidth(gyro_250Hz);//set gyroscope bandwidth
  print_data();//print some data
  Serial.println("");

  //set gyroscope bandwidth to 5Hz and accelerometer bandwidth to 5Hz
  Serial.println("Gyro bandwidth : 5Hz");
  Serial.println("Acc bandwidth  : 5Hz");
  delay(4000);
  mpu.set_acc_bandwidth(acc_5Hz);//set accelerometer bandwidth
  mpu.set_gyro_bandwidth(gyro_5Hz);//set gyroscope bandwidth
  print_data();//print some data
  Serial.println("");
}
