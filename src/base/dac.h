/**
 * @file dac.h
 */

#ifndef DAC_H
#define DAC_H
#include <SPI.h>

#define CS1 PA4
#define CS2 PC15

void dac_write(int ch, int cv);
void calibrate(int val);
#endif
