/**
 * @file gate.h
 * @brief Some define and functions for gates.
 */
#ifndef CONFIG_H
#define CONFIG_H
#include <Arduino.h>

#define CLOCK_IN  PA3
#define CLOCK_OUT PB3
#define GATE_1    PB5
#define GATE_2    PB4 
#define DRUM_2    PB8 
#define DRUM_1    PB9

/**
 * @brief Gates (leds) list. 
 *
 * @remark Sort from left to right.
 */
const byte gates[5] = {
    CLOCK_OUT, DRUM_1, DRUM_2, GATE_1, GATE_2};

/**
 * @brief 5 output set HIGH by default and input pull up for encoders.
 *
 * @remark NPN switching output 
 */
void pin_init();

/**
 * @brief At start the gate turn off (led turn on) from left to right.
 *
 * If there is a bug, the led turn off.
 */
void gates_test();
#endif
