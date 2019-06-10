#ifndef MPU9255_H
#define MPU9255_H

#include <Arduino.h>
#include <Wire.h>

///modules (for enable / disable / reset functions)
enum modules
{
  Acc_X,//accelerometer X axis
  Acc_Y,//accelerometer Y axis
  Acc_Z,//accelerometer Z axis
  Gyro_X,//gyroscope X axis
  Gyro_Y,//gyroscope Y axis
  Gyro_Z,//gyroscope Z axis
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

//axis
enum axis
{
  X_axis,
  Y_axis,
  Z_axis,
};

//bandwidth
enum bandwidth
{
  gyro_8800Hz,
  gyro_3600Hz,
  gyro_250Hz,
  gyro_184Hz,
  gyro_92Hz,
  gyro_41Hz,
  gyro_20Hz,
  gyro_10Hz,
  gyro_5Hz,
  acc_1113Hz,
  acc_460Hz,
  acc_184Hz,
  acc_92Hz,
  acc_41Hz,
  acc_20Hz,
  acc_10Hz,
  acc_5Hz,
};


//interrupt pin settings
enum interrupt_pin
{
  active_low,//interrupt pin gets low when active
  active_high,//interrupt pin gets high when active
  open_drain,//open drain mode
  push_pull,//push-pull mode
  pulse_output,//pulse type output
  latched_output,//latch type output
};

//available interrupts
enum interrupts
{
  motion_interrupt,//motion detection
  FIFO_overflow_interrupt,//fifo overflow
  Fsync_interrupt,//fsync interrupts
  raw_rdy_interrupt,//raw readings ready
};

class MPU9255
{
public:

  //acceleration raw data
  int16_t ax=0;//X axis
  int16_t ay=0;//Y axis
  int16_t az=0;//Z axis

  //gyroscope raw data
  int16_t gx=0;//X axis
  int16_t gy=0;//Y axis
  int16_t gz=0;//Z axis

  //magnetometer raw data
  int16_t mx=0;//X axis
  int16_t my=0;//Y axis
  int16_t mz=0;//Z axis

  //general control
  uint8_t init();//initialize MPU9255
  void set_acc_scale(scales selected_scale);//set accelerometer scale
  void set_gyro_scale(scales selected_scale);//set gyroscope scale
  void set_acc_offset(axis selected_axis, int16_t offset);//set accelerometer offset
  void set_gyro_offset(axis selected_axis, int16_t offset);//set gyroscope offset
  void set_acc_bandwidth(bandwidth selected_bandwidth);//set accelerometer bandwidth
  void set_gyro_bandwidth(bandwidth selected_bandwidth);//set gyroscope bandwidth
  uint8_t testIMU();//test gyroscope and accelerometer
  uint8_t testMag();//test magnetometer

  //interrupt configuration
  void set_INT_active_state(interrupt_pin selected_mode);//set INT pin (interrupt pin) active state
  void set_INT_pin_mode(interrupt_pin selected_mode);//set INT PIN operation mode (open drain or push-pull)
  void set_INT_signal_mode(interrupt_pin selected_mode);//set INT pin signal type (pulse or latched)
  void enable_interrupt_output(interrupts selected_interrupt);//enable interrupt output
  void disable_interrupt_output(interrupts selected_interrupt);//disable interrupt output
  void clear_interrupt();//clear interrupt flags

  //motion interrupt
  void set_motion_threshold_level(uint8_t threshold);//set threshold level for motion detection
  void enable_motion_interrupt();//enable motion interrupt
  void disable_motion_interrput();//disable motion interrupt

  //

  //reset
  void Hreset();//hard reset
  void reset(modules selected_module);//reset selected module

  //measurements
  void read_acc();//read data from the accelerometer
  void read_gyro();//read data from the gyroscope
  void read_mag();//read data from the magnetometer
  int16_t read_temp();//read temperature

  //power control
  void sleep_enable();//enable sleep mode
  void sleep_disable();//disable sleep mode
  void disable(modules selected_module);//disable selected module
  void enable(modules selected_module);//enable selected module

  //magnetometer sensitivity
  double mx_sensitivity;//X axis
  double my_sensitivity;//Y axis
  double mz_sensitivity;//Z axis

  private:
  void requestBytes(uint8_t address, uint8_t subAddress, uint8_t bytes);//request data
  uint8_t read(uint8_t address, uint8_t subAddress);//read one byte from selected register
  void readArray(uint8_t *output, char size);//read an array of bytes
  void write(uint8_t address, uint8_t subAddress, uint8_t data);//write one byte of data to the register
  void write_OR(uint8_t address, uint8_t subAddress, uint8_t data);//write one byte of data to the register (with OR operation)
  void write_AND(uint8_t address, uint8_t subAddress, uint8_t data);//write one byte of data to the register (with AND operation)
  int16_t uint8ToUint16(uint8_t Lbyte, uint8_t Hbyte);//convert two bytes into one 16 bit value
  uint8_t getScale(uint8_t current_state, scales selected_scale);//convert scale value into register value

  //accelerometer factory offset
  int AX_offset;//X axis
  int AY_offset;//Y axis
  int AZ_offset;//Z axis

  //gyroscope factory offset
  int GX_offset;//X axis
  int GY_offset;//Y axis
  int GZ_offset;//Z axis

  //registers map
  enum registers
  {
    //sensor addresses
    MAG_address       = 0x0C,//magnetometer
    MPU_address       = 0x68,//main chip

    //main chip
    USER_CTRL         = 0x6A,
    PWR_MGMT_1        = 0x6B,
    PWR_MGMT_2        = 0x6C,
    SIGNAL_PATH_RESET = 0x68,
    INT_PIN_CFG       = 0x37,
    ST1               = 0x02,
    ACCEL_CONFIG      = 0x1C,
    ACCEL_CONFIG_2    = 0x1D,
    MOT_DETECT_CTRL   = 0x69,
    WOM_THR           = 0x1F,
    GYRO_CONFIG       = 0x1B,
    CONFIG            = 0x1A,
    SMPLRT_DIV        = 0x19,
    INT_ENABLE        = 0x38,
    INT_STATUS        = 0x3A,
    WHO_AM_I          = 0x75,

    //gyroscope offset
    XG_OFFSET_H       = 0x13,
    XG_OFFSET_L       = 0x14,
    YG_OFFSET_H       = 0x15,
    YG_OFFSET_L       = 0x16,
    ZG_OFFSET_H       = 0x17,
    ZG_OFFSET_L       = 0x18,

    //accelerometer offset
    XA_OFFSET_H       = 0x77,
    XA_OFFSET_L       = 0x78,
    YA_OFFSET_H       = 0x7A,
    YA_OFFSET_L       = 0x7B,
    ZA_OFFSET_H       = 0x7D,
    ZA_OFFSET_L       = 0x7E,

    //magnetometer
    MAG_ID            = 0x00,
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
};

#endif
