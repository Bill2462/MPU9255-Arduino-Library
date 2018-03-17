#ifndef MPU9255_H
#define MPU9255_H

#include <Arduino.h>
#include <Wire.h>

///modules (for enable / disable / reset functions)
enum modules
{
  AX,//accelerometer X axis
  AY,//accelerometer Y axis
  AZ,//accelerometer Z axis
  GX,//gyroscope X axis
  GY,//gyroscope Y axis
  GZ,//gyroscope Z axis
  magnetometer,//magnetometer
  accelerometer,//accelerometer
  gyroscope,//gyroscope
  thermometer,//thermometer
  signalPaths,//all signal paths
};

//available scales
enum scales
{
  scale_2g,//+-2g
  scale_4g,//+-4g
  scale_8g,//+-8g
  scale_16g,//+-16g
  scale_250dps,//+-250 degrees per second
  scale_500dps,//+- 500 degrees per second
  scale_1000dps,//+- 1000 degrees per second
  scale_2000dps,//+- 2000 degrees per second
};

class MPU9255
{
public:

  ///register map
  enum registers
  {
    //sensor adresses
    MAG_address        = 0x0C,//magnetometer
    MPU_address        = 0x68,//main chip

    //main chip
    USER_CTRL         = 0x6A,
    PWR_MGMT_1        = 0x6B,
    PWR_MGMT_2        = 0x6C,
    SIGNAL_PATH_RESET = 0x68,
    INT_PIN_CFG       = 0x37,
    ST1               = 0x02,
    ACCEL_CONFIG      = 0x1C,
    GYRO_CONFIG       = 0x1B,
    CONFIG            = 0x1A,
    SMPLRT_DIV        = 0x19,
    INT_ENABLE        = 0x38,

    //magnetometer
    CNTL              = 0x0A,
    CNTL2             = 0x0B,
    ASAX              = 0x10,
    ASAY              = 0x11,
    ASAZ              = 0x12,

    /// data registers
    MAG_XOUT_L        = 0x03,//magnetometer
    GYRO_XOUT_H       = 0x43,//gyro
    ACCEL_XOUT_H      = 0x3B,//accelerometer
    TEMP_OUT_H        = 0x41,//thermometer

  };

  //acceleration data
  int16_t ax=0;//X axis
  int16_t ay=0;//Y axis
  int16_t az=0;//Z axis

  //gyroscope data
  int16_t gx=0;//X axis
  int16_t gy=0;//Y axis
  int16_t gz=0;//Z axis

  //magnetometer data
  int16_t mx=0;//X axis
  int16_t my=0;//Y axis
  int16_t mz=0;//Z axis

  //general control
  void init();//Initialize magnetometer and IMU
  void set_acc_scale(scales selected_scale);//Set accelerometer scale
  void set_gyro_scale(scales selected_scale);//Set gyroscope scale

  //reset
  void Hreset();//Hard reset - Resets entire chip (call of init function is required to use chip afterwards)
  void reset(modules selected_module);// reset a module

  //data read function
  void read_acc();//read data from accelerometer
  void read_gyro();//read data from gyroscope
  void read_mag();//read data from magnetometer
  int16_t read_temp();//read temperature from the internal sensor (EXPERIMENTAL!)

  //power control
  void sleep_enable();//put main chip in a sleep mode
  void sleep_disable();//disable sleep mode
  void disable(modules selected_module);//disable something
  void enable(modules selected_module);//enable something

  double mx_sensitivity, my_sensitivity, mz_sensitivity;//magnetometer mx_sensitivity for compensation

  private:
  void requestBytes(uint8_t address, uint8_t subAddress, uint8_t bytes);//request bytes from some device
  uint8_t read(uint8_t address, uint8_t subAddress);//read one byte from register
  void readArray(uint8_t *output, char size);//read an array of bytes
  void write(uint8_t address, uint8_t subAddress, uint8_t data);//write one byte of data to the register
  void write_OR(uint8_t address, uint8_t subAddress, uint8_t data);//write one byte of data to the register (with OR operation)
  void write_AND(uint8_t address, uint8_t subAddress, uint8_t data);//write one byte of data to the register (with AND operation)
  int16_t uint8ToUint16(uint8_t Lbyte, uint8_t Hbyte);//put together two bytes into one 16 bit variable
  uint8_t getScale(uint8_t current_state, scales selected_scale);//get register value for a scale
};

#endif
