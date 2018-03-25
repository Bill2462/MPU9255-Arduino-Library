#include <MPU9255.h>//include MPU9255 library

MPU9255 mpu;

void setup() {
  Serial.begin(115200);//initialize Serial port
  mpu.init();//initialize MPU9255 chip

  //setup motion interrupt
  mpu.set_motion_threshold_level(200);//set motion treshold level to 800 mg (4 mg per LSB)
  mpu.enable_motion_interrupt();//enable motion interrupt

  //setup interrupt pin (INT) configuration
  mpu.set_INT_active_state(active_high);//INT pin will go high when interrupt is triggered
  mpu.set_INT_pin_mode(push_pull);//set INT pin to operate in push-pull mode (no external pullup resistors required)
  mpu.set_INT_signal_mode(latched_output);//set output signal to latch mode (pin will go high and remain high until interrupt flag is cleared).
  mpu.enable_interrupt_output(motion_interrupt);//enable motion interrupt to propagate throught INT pin

  //arduino input pin configuration
  pinMode(2,INPUT);

  //LED pin
  pinMode(LED_BUILTIN,OUTPUT);
}

void loop() {
   //check whether the motion interrupt is triggered
   if(digitalRead(2) == HIGH)
   {
     mpu.clear_interrupt();//clear interrupt flag (INT pin will be pulled LOW)
     digitalWrite(LED_BUILTIN,HIGH);//turn the LED on
     delay(1000);//wait 1s
     digitalWrite(LED_BUILTIN,LOW);//turn the LED off
   }
}
