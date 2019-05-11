
## Power / Reset control

`void sleep_enable()`

Enable sleep mode. 

 - Parameters: None
 - Returns: None
 
 ----------------------

`void sleep_disable()`

Disables sleep mode.

 - Parameters: None
 - Returns: None

----------------------

`void disable(modules selected_module)`

Disables selected module.

 - Parameters: 
   - `modules selected_module` - Selected module.
 - Returns: None.
 
 Valid Selected module parameter values:
 - `AX` - accelerometer X axis
 - `AY` - accelerometer Y axis
 - `AZ` - accelerometer Z axis
 - `GX` - gyroscope X axis
 - `GY` - gyroscope Y axis
 - `GZ` - gyroscope Z axis
 - `magnetometer` - magnetometer
 
 --------------------

`void enable(modules selected_module)`

Enables selected module. 

 - Parameters: 
   - `modules selected_module` - Selected module.
 - Returns: None.
 
 Valid Selected module parameter values:
 - `AX` - accelerometer X axis
 - `AY` - accelerometer Y axis
 - `AZ` - accelerometer Z axis
 - `GX` - gyroscope X axis
 - `GY` - gyroscope Y axis
 - `GZ` - gyroscope Z axis
 - `magnetometer` - magnetometer

---------------------

`void Hreset()`

Perform hard reset. All registers will be restored to their default state.

 - Parameters: None
 - Returns: None
 
 -------------------

void reset(modules selected_module)

Reset selected module.

 - Parameters : 
    - `modules selected_module` - selected module 
 - Returns : None.

Valid Selected module parameter values (modules that can be reset)

 - `magnetometer` - magnetometer
 - `accelerometer` - accelerometer
 - `gyroscope` - gyroscope
 - `thermometer` - thermometer
 - `signalPaths` - all signal paths
