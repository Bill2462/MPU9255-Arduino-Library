/*
sleep example
This example shows how to enable and disable sleep mode.
*/

#include <MPU9255.h>//include MPU9255 library

MPU9255 mpu;

void print_data()//take some raw readings and print them in serial monitor
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
  Serial.println("Taking some measurements...");
  print_data();//take some readings

  Serial.println("Entering sleep mode...");
  mpu.disable(magnetometer);//disable magnetometer
  mpu.sleep_enable();//put main chip in a sleep mode
  delay(10000);//wait 10 seconds

  Serial.println("Disabling sleep mode...");
  mpu.sleep_disable();//disable sleep mode
  mpu.enable(magnetometer);//enable magnetometer

  Serial.println("");
}
