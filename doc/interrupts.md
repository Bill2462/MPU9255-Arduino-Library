# Interrupts 


## General interrupt configuration

`void set_INT_active_state(interrupt_pin selected_mode)`

Set INT pin (MPU9255 interrupt output pin) active state. 

- Parameters: 
  - `interrupt_pin selected_mode` - Selected active state. 
- Returns: None

Valid values of selected active state parameter:
- `active_low` - Pin will go low when interrupt is detected. 
- `active_high` - Pin will go high when interrupt is detected. 

--------------

`void set_INT_pin_mode(interrupt_pin selected_mode)`

Set INT pin operation mode. 

- Parameters: 
  - `interrupt_pin selected_mode` - Selected mode. 
- Returns: None

Valid pin modes:
- `open_drain` - Pin will operate in open-drain mode (external pullup resistor is required). 
- `push_pull` - Pin will operate in push-pull mode (no external components required). 

--------------

`void set_INT_signal_mode(interrupt_pin selected_mode)`

Set INT pin output signal mode. 

- Parameters: 
  - `interrupt_pin selected_mode` - Selected output signal mode. 
- Returns: None

Valid output signal modes:
- `latched_output` - When interrupt is detected, pin will go into active state until interrupt flag is cleared. 
- `pulse_output` -  When interrupt is detected, pin will generate short pulse. 

-----------------------

`void enable_interrupt_output(interrupts selected_interrupt)`

Enable selected interrupt to propagate to interrupt pin.

- Parameters: 
  - `interrupts selected_interrupt` - Selected interrupt. 
- Returns: None

Valid vales of Selected interrupt parameter : 
 - `motion_interrupt` - motion interrupt
 - `FIFO_overflow_interrupt` - FIFO overflow
 - `Fsync_interrupt` - Fsync interrupt
 - `raw_rdy_interrupt` - raw_rdy interrupt
 
 ------------------

`void disable_interrupt_output(interrupts selected_interrupt)`

Prevent selected interrupt from propagating to interrupt pin.

- Parameters: 
  - `interrupts selected_interrupt` - Selected interrupt. 
- Returns: None

Valid vales of Selected interrupt parameter : 
 - `motion_interrupt` - motion interrupt
 - `FIFO_overflow_interrupt` - FIFO overflow
 - `Fsync_interrupt` - Fsync interrupt
 - `raw_rdy_interrupt` - raw_rdy interrupt

--------------------

`void clear_interrupt()`

Clear interrupt flags. 

- Parameters: None
- Returns: None

-------------------

## Motion interrupt 

`void set_motion_threshold_level(uint8_t threshold)`

Set motion interrupt threshold level. 

- Parameters: 
  - `uint8_t threshold` -Tthreshold value of shock that will cause an interrupt.( 4mg per LSB). 
- Returns: None

`void enable_motion_interrupt()`

Enable motion interrupt.

- Parameters: None
- Returns: None

------------------

`void disable_motion_interrput()`

Disable motion interrupt. 

- Parameters: None
- Returns: None
