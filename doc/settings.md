## Utilities

`void init()`

Initializes all internal components. Must be called before any other operation.
- Parameters : None 
- Returns : None

------------------

`uint8_t testIMU()`

Tests connection with IMU (accelerometer and gyrosocope).
- Parameters : None 
- Returns : 0 if success 1 if failure

------------------

`uint8_t testMag()`

Tests connection with magnetometer.
- Parameters : None 
- Returns : 0 if success 1 if failure

------------------

`void set_acc_scale(scales selected_scale)`

Selects Accelerometer scale.

 - Parameters : 
    - `scales selected_scale` - selected scale.
 - Returns : None

Valid selected scale parameter values:

- `scale_2g`  - +-2g
- `scale_4g`  - +-4g
- `scale_8g`  - +-8g
- `scale_16g `- +-16g

 -------------------------------
 
`void set_gyro_scale(scales selected_scale)`

Selects gyroscope scale.

 - Parameters : 
    - `scales selected_scale` - selected scale.
 - Returns : None.

Valid selected scale parameter values:
 - `scale_250dps`  - +-250 degrees per second
 - `scale_500dps`  - +-500 degrees per second
 - `scale_1000dps` - +-1000 degrees per second
 - `scale_2000dps` - +-2000 degrees per second

--------------------------------

`void set_acc_offset(axis selected_axis, int16_t offset)`

Set offset on selected accelerometer axis. 

- Parameters: 
  - `axis selected_axis` - selected axis
  - `int16_t offset`     - offset
- Returns: None

IMPORTANT NOTE : Despite of being stored in 16 bit variable, offset is a 15 bit signed number. 

Valid selected axis parameter values : 
- `X_axis` - X axis
- `Y_axis` - Y axis
- `Z_axis` - Z axis

-----------------------------

`void set_gyro_offset(axis selected_axis, int16_t offset)`

Set offset on selected gyroscope axis. 

- Parameters: 
  - `axis selected_axis` - selected axis
  - `int16_t offset`     - offset
- Returns: None

IMPORTANT NOTE: Gyroscope offset is a 16 bit signed number. 

Valid selected axis parameter values : 
- `X_axis` - X axis
- `Y_axis` - Y axis
- `Z_axis` - Z axis

-----------------------------

`void set_acc_bandwidth(bandwidth selected_bandwidth)`

Select accelerometer bandwidth. 

- Parameters : 
  - `bandwidth selected_bandwidth` - selected bandwidth
- Returns : None

Valid selected bandwidth parameter values : 
- `acc_1113Hz` - 1113 Hz
- `acc_460Hz`  - 460Hz
- `acc_184Hz`  - 184Hz
- `acc_92Hz`   - 92Hz
- `acc_41Hz`   - 41Hz
- `acc_20Hz`   - 20Hz
- `acc_10Hz`   - 10Hz
- `acc_5Hz`    - 5Hz

----------------------------

`void set_gyro_bandwidth(bandwidth selected_bandwidth)`

Select gyroscope bandwidth. 

- Parameters : 
  - `bandwidth selected_bandwidth` - selected bandwidth
- Returns : None

Valid selected bandwidth parameter values : 
 - `gyro_8800Hz` - 8800Hz
 - `gyro_3600Hz` - 3600Hz
 - `gyro_250Hz`  - 250Hz
 - `gyro_184Hz`  - 184Hz
 - `gyro_92Hz`   - 92Hz
 - `gyro_41Hz`   - 41Hz
 - `gyro_20Hz`   - 20Hz
 - `gyro_10Hz`   - 10Hz
 - `gyro_5Hz `   - 5Hz
