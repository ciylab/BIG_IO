/**
 * @file dac.h
 * @brief dac functions.
 */

#ifndef DAC_H
#define DAC_H
#include <Arduino.h>

#define CS1 PA4    //!< dual DAC.
#define CS2 PC15   //!< simple DAC.

/**
 * @brief SPI output gates.
 */
void init_dac();

/**
 * @brief SPI write function.
 *
 *  Build the 16-bit command word:\n
 *  Bit 15: A/B (0 for MCP4921)\n
 *  Bit 14: Buffered VREF (0 = unbuffered, 1 = buffered)\n
 *  Bit 13: Output Gain (1 = 1x, 0 = 2x)\n
 *  Bit 12: Shutdown control (1 = active operation)\n
 *  Bits 11-0: 12-bit data value\n
 *
 * @param ch channel 0, 1 or 2
 * @param cv int between 0 and 4095
 */
void dac_write(byte ch, int cv);

/**
 * @brief To calibrate CVs.
 *
 * 4 volts = C4 on CV1 (2 volts = C2 on CV2 and 1 volt = C1 on CV3).
 * @param val value on encoder. 
 * @return the cv for exactly 4 volts for the project is C4RefVolt.
 * @see Modules::C4RefVolt
 */
void calibrate(byte val);

/**
 * @brief For cv
 * 
 * The value is calculated from C4RefVolt
 * @param pitch the midi note number
 * @return the cv value
 */
int getVoltage(byte pitch);
#endif
