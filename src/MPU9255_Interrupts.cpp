#include "MPU9255.h"
#include "Arduino.h"

void MPU9255::set_INT_signal_mode(interrupt_pin selected_mode)
{
  //if latch mode is selected
  if(selected_mode == latched_output)
  {
    write_OR(MPU_address,INT_PIN_CFG,(1<<5));//set LATCH_INT_EN bit
  }
}

void MPU9255::clear_interrupt()
{
  read(MPU_address,INT_STATUS);//read interrupt status register to clear the pin state
}

void MPU9255::set_INT_active_state(interrupt_pin selected_mode)
{
  switch (selected_mode)
  {
    case active_low:
      write_OR(MPU_address,INT_PIN_CFG,(1<<7));
      break;

    case active_high:
      write_AND(MPU_address,INT_PIN_CFG,~(1<<7));
      break;
  }
}

void MPU9255::set_INT_pin_mode(interrupt_pin selected_mode)
{
  switch (selected_mode)
  {
    case open_drain:
      write_OR(MPU_address,INT_PIN_CFG,(1<<6));
      break;

    case push_pull:
      write_AND(MPU_address,INT_PIN_CFG,~(1<<6));
      break;
  }
}

void MPU9255::enable_interrupt_output(interrupts selected_interrupt)
{
  switch(selected_interrupt)
  {
    case motion:
      write_OR(MPU_address,INT_ENABLE,(1<<6));
      break;

    case FIFO_overflow:
      write_OR(MPU_address,INT_ENABLE,(1<<4));
      break;

    case Fsync:
      write_OR(MPU_address,INT_ENABLE,(1<<3));
      break;

    case raw_rdy:
      write_OR(MPU_address,INT_ENABLE,(1<<0));
      break;
  }
}

void MPU9255::disable_interrupt_output(interrupts selected_interrupt)
{
  switch(selected_interrupt)
  {
    case motion_interrupt:
      write_OR(MPU_address,INT_ENABLE,~(1<<6));
      break;

    case FIFO_overflow_interrupt:
      write_OR(MPU_address,INT_ENABLE,~(1<<4));
      break;

    case Fsync_interrupt:
      write_OR(MPU_address,INT_ENABLE,~(1<<3));
      break;

    case raw_rdy_interrupt:
      write_OR(MPU_address,INT_ENABLE,~(1<<0));
      break;
  }
}

void MPU9255::set_motion_threshold_level(uint8_t threshold)
{
  write(MPU_address,WOM_THR,threshold);//write treshold value to the WOM_THR register
}

void MPU9255::enable_motion_interrupt()
{
  write(MPU_address,MOT_DETECT_CTRL,(1<<7)|(1<<7));
}

void MPU9255::disable_motion_interrput()
{
  write(MPU_address,MOT_DETECT_CTRL,~((1<<7)|(1<<7)));
}
