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
#define CLOCK_OUT D6
#define DRUM_1    D5 
#define DRUM_2    D4
#define GATE_1    D3
#define GATE_2    D2
#define CLK1      A1
#define DT1       A2
#define SW1       A3
#define CLK2      D8
#define DT2       D7
#define SW2       D9
#elif bluepill
#define CS1       PA4    //!< dual DAC.
#define CS2       PC15   //!< simple DAC.
#define CLOCK_IN  PA3
#define CLOCK_OUT PB3
#define DRUM_1    PB5 
#define DRUM_2    PB4
#define GATE_1    PB9
#define GATE_2    PB8
#define CLK1      PB0
#define DT1       PB1
#define SW1       PB10
#define CLK2      PA1
#define DT2       PA0
#define SW2       PA2
#endif

#endif
