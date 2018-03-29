## Measurements

`void read_acc()`

Reads raw readings from accelerometer data registers. 

 - Parameters: None
 - Returns: None

-----------------------

`void read_gyro()`

Reads raw readings from gyroscope data registers. 

 - Parameters: None
 - Returns: None
 
 ----------------------

`void read_mag()`

Reads raw readings from magnetometr data registers. 

 - Parameters: None
 - Returns: None
 
 ---------------------

`int16_t read_temp()`

Read dice temperature. 

 - Parameters: None
 - Returns: Temperature (as a `int16_t` value)
 
-----------------------

Raw readings from each axis of accelerometer, gyroscope and magnetometer are stored in pulic variables :

Accelerometer :

 - `int16_t ax` - X axis acceleration.
 - `int16_t ay` - Y axis acceleration.
 - `int16_t az` - Z axis acceleration.

Gyroscope :

 - `int16_t gx` - X axis angular velocity.
 - `int16_t gy` - Y axis angular velocity.
 - `int16_t gz` - Z axis angular velocity.

Magnetometer :

 - `int16_t mx` - X axis magnetic field strength.
 - `int16_t my` - Y axis magnetic field strength.
 - `int16_t mz` - Z axis magnetic field strength.
