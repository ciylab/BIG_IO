/**
 * @file pins.h
 * @brief pins definition
 */

#ifndef PINS_H
#define PINS_H

#ifdef nanor4
#define LED       A7
#define CS1       D10    //!< dual DAC.
#define CS2       A0     //!< simple DAC.
#define CLOCK_IN  A6
#define GATE_3    D6
#define DRUM      D5 
#define CLOCK_OUT D2
#define GATE_1    D3
#define GATE_2    D4
#define CLK1      A2
#define DT1       A1
#define SW1       A3
#define CLK2      D7
#define DT2       D8
#define SW2       D9
#elif bluepill
#define CS1       PB0    //!< dual DAC.
#define CS2       PA3    //!< simple DAC.
#define CLOCK_IN  PA8
#define CLOCK_OUT PB14
#define DRUM      PB12
#define GATE_3    PB15
#define GATE_1    PB13
#define GATE_2    PA11
#define CLK1      PA4
#define DT1       PA6
#define SW1       PB1
#define CLK2      PA1
#define DT2       PA0
#define SW2       PA2
#endif

#endif
