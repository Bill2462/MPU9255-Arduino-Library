/**
 * @file MPU9255_Interrupts.cpp
 * @brief This source file contains methods for setting up interrupts.
 */

// This file is a part of MPU9255 library.
// Copyright (c) 2017-2020 Krzysztof Adamkiewicz <kadamkiewicz835@gmail.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the “Software”), to deal in the
// Software without restriction, including without limitation the rights to use, copy,
// modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
// and to permit persons to whom the Software is furnished to do so, subject to the
// following conditions: THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
// OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include "MPU9255.h"
#include "Arduino.h"

//set interrupt signal mode
//Parameters:
// * interrupt_pin selected_mode - selected_mode
void MPU9255::set_INT_signal_mode(interrupt_pin selected_mode)
{
  switch(selected_mode)
  {
    case latched_output://if latch mode is selected
      write_OR(MPU_address,INT_PIN_CFG,(1<<5));//set LATCH_INT_EN bit
      break;

    case pulse_output://if pulse mode is selected
        write_AND(MPU_address,INT_PIN_CFG,~(1<<5));//clear LATCH_INT_EN bit
        break;
  }
}

//clear interrupt flags (this also clears interrupt pin)
void MPU9255::clear_interrupt()
{
  read(MPU_address,INT_STATUS);//read interrupt status register to clear the flags
}

//set INT pin (interrupt pin ) active state
//Parameters:
// * interrupt_pin selected_mode - selected state
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

//set interrupt pin mode
//Parameters:
// * interrupt_pin selected_mode - selected mode
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

//enable interrupt signal to propagate to the output pin
//Parameters:
// * interrupts selected_interrupt - selected interrupt
void MPU9255::enable_interrupt_output(interrupts selected_interrupt)
{
  switch(selected_interrupt)
  {
    case motion_interrupt:
      write_OR(MPU_address,INT_ENABLE,(1<<6));
      break;

    case FIFO_overflow_interrupt:
      write_OR(MPU_address,INT_ENABLE,(1<<4));
      break;

    case Fsync_interrupt:
      write_OR(MPU_address,INT_ENABLE,(1<<3));
      break;

    case raw_rdy_interrupt:
      write_OR(MPU_address,INT_ENABLE,(1<<0));
      break;
  }
}

//enable interrupt signal to propagate to the output pin
//Parameters:
// * interrupts selected_interrupt - selected interrupt
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

//set motion threshold level
//Parameters:
// * uint8_t threshold - selected threshold
void MPU9255::set_motion_threshold_level(uint8_t threshold)
{
  write(MPU_address,WOM_THR,threshold);//write threshold value to the WOM_THR register
}

//enable motion interrupt
void MPU9255::enable_motion_interrupt()
{
  write(MPU_address,MOT_DETECT_CTRL,(1<<7)|(1<<7));
}

//disable motion interrupt
void MPU9255::disable_motion_interrput()
{
  write(MPU_address,MOT_DETECT_CTRL,~((1<<7)|(1<<7)));
}
