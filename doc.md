## MPU9255 Arduino Library documentation

### Classes : 

`class MPU9255`

Library main class. All library functions are declared inside that class. 

### General control 

`void init()`

Initializes all internal components. Must be called before any other operation.



### Measurements 

`void read_acc()`

Reads raw data from the accelerometer. 

------------------------------

`void read_gyro()`

Reads raw data from the gyroscope. 

------------------------------

`void read_mag()`

Reads raw data from the magnetometer. 

------------------------------

`int16_t read_temp()`

Reads temperature using MPU9255 internal temperature sensor. 
Temperature is returned as a 16 bit number. 

Arguments : None

Returns : Temperature (int16_t). 

------------------------------

Raw readings from each axis of accelerometer, gyroscope and magnetometer are stored in pulic variables : 

Accelerometer :

`int16_t ax` - X axis acceleration.

`int16_t ay` - Y axis acceleration.

`int16_t az` - Z axis acceleration.

Gyroscope : 

`int16_t gx` - X axis angular velocity.

`int16_t gy` - Y axis angular velocity.

`int16_t gz` - Z axis angular velocity.


Magnetometer : 

`int16_t mx` - X axis magnetic field strength.

`int16_t my` - Y axis magnetic field strength.

`int16_t mz` - Z axis magnetic field strength.

------------------------------

`void set_acc_scale(scales selected_scale)`

Selects Accelerometer scale.

Parameters  : Selected scale. 

Returns : None.

Available accelerometer scales : 
- scale_2g - +-2g
- scale_4g - +-4g
- scale_8g - +-8g
- scale_16g - +-16g

------------------------------

`void set_gyro_scale(scales selected_scale)`

Selects gyroscope scale. 

Parameters  : Selected scale. 

Returns : None.

Available gyroscope scales : 
- scale_250dps - +-250 degrees per second
- scale_500dps - +-500 degrees per second
- scale_1000dps - +-1000 degrees per second
- scale_2000dps - +-2000 degrees per second

### Power control

`void sleep_enable()`

Puts chip in a sleep mode. 
In a sleep mode all sensors are disabled but configuration registers are keeping their values. 

------------------------------

`void sleep_disable()`

Disables sleep mode. 

------------------------------


`void disable(modules selected_module)`

Disables selected module. 

Parameters : Selected module. 

Returns : None. 


------------------------------

`void enable(modules selected_module)`

Reenables selected module. 

Parameters  : Selected module. 

Returns : None. 

Modules that can be disabled / enabled : 

- AX - accelerometer X axis
- AY - accelerometer Y axis
- AZ - accelerometer Z axis
- GX - gyroscope X axis
- GY - gyroscope Y axis
- GZ - gyroscope Z axis
- magnetometer - magnetometer



### Reset control

`void Hreset()`

Perform hard reset. All registers will be restored to their default state. 

Note: `void init()` function must be called afterwards to continue using the chip. 

------------------------------

`void reset(modules selected_module)`

Reset selected module. 

Parameters : Selected module. 

Returns : None. 

Modules that can be resetted : 
- magnetometer - magnetometer
- accelerometer - accelerometer
- gyroscope - gyroscope
- thermometer - thermometer
- signalPaths - all signal paths


