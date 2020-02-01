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

/**
 * @brief Set interrupt signal mode.
 * @param selected_mode Selected mode.
 */
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

/**
 * @brief Clear interrupt flag (this also clears interrupt pin).
 */
void MPU9255::clear_interrupt()
{
  read(MPU_address,INT_STATUS);//read interrupt status register to clear the flags
}

/**
 * @brief Set interrupt pin active state.
 * @param selected_mode Interrupt pin active state.
 */
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

/**
 * @brief Set interrupt pin mode.
 * @param selected_mode Interrupt pin mode of operation.
 */
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

/**
 * @brief Enable interrupt.
 * @param selected_interrupt Interrupt to be enabled.
 */
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

/**
 * @brief Disable interrupt.
 * @param selected_interrupt Interrupt to be disabled.
 */
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

/**
 * @brief Set motion detector threeshold level.
 * @param threshold Threshold value.
 */
void MPU9255::set_motion_threshold_level(uint8_t threshold)
{
  write(MPU_address,WOM_THR,threshold);//write threshold value to the WOM_THR register
}

/**
 * @brief Enable motion detector interrupt.
 */
void MPU9255::enable_motion_interrupt()
{
  write(MPU_address,MOT_DETECT_CTRL,(1<<7)|(1<<7));
}

/**
 * @brief Disable motion detector interrupt.
 */
void MPU9255::disable_motion_interrput()
{
  write(MPU_address,MOT_DETECT_CTRL,~((1<<7)|(1<<7)));
}
