/**
 * @file dac.h
 */

#ifndef DAC_H
#define DAC_H
#include <Arduino.h>

void init_dac();
void dac_write(byte ch, int cv);
unsigned int calibrate(byte val);
#endif
