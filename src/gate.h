/**
 * @file gate.h
 * @brief Some define and functions for gates.
 */
#ifndef CONFIG_H
#define CONFIG_H
#include <Arduino.h>
#include "pins.h"

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
