#include "MPU9255.h"
#include "Arduino.h"


uint8_t MPU9255::getScale(uint8_t current_state, scales selected_scale)
{
  if(selected_scale == scale_2g || selected_scale == scale_250dps)
  {
    current_state &= ~((1<<3)|(1<<4));
  }

  if(selected_scale == scale_4g || selected_scale == scale_500dps)
  {
    current_state &= ~(1<<4);
    current_state |= (1<<3);
  }

  if(selected_scale == scale_8g || selected_scale == scale_1000dps)
  {
    current_state &= ~(1<<3);
    current_state |= (1<<4);
  }

  if(selected_scale == scale_16g || selected_scale == scale_2000dps)
  {
    current_state |= (1<<4)|(1<<3);
  }

  return current_state;
}

/* Set accelerometer scale
Arguments:
- Selected scale
Returns : None
*/
void MPU9255::set_acc_scale(scales selected_scale)
{
	uint8_t val = read(MPU_address,ACCEL_CONFIG);//read old register value
  	val = getScale(val,selected_scale);
	write(MPU_address,ACCEL_CONFIG,val);// commit changes
}

/* Set gyroscope scale
Arguments:
- Selected scale
Returns : None
*/
void MPU9255::set_gyro_scale(scales selected_scale)
{
	uint8_t val=read(MPU_address,GYRO_CONFIG);//read old register value
  	val = getScale(val,selected_scale);
	write(MPU_address,GYRO_CONFIG,val);// commit changes
}
