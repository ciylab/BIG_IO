/**
 * @file config.h
 * @brief Some data used in project.
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

#define MAIN 0
#define CONF 1
#define IO   2
#define PLAY 3
#define TIME 4

/**
 * @brief Leds list. 
 *
 * @remark Sort by left to right.
 */
const byte pins[5] = {
    CLOCK_OUT, DRUM_1, DRUM_2, GATE_1, GATE_2};

/**
 * @struct parameter
 * @brief For any parameter of the project.
 * 
 * Value changes by right encoder. Buffer can be used when
 * value change during note off for example. 
 * Its id is **cursor_num**.
 */
typedef struct parameter {
    char name[8];    //!<  name to display
    byte value;      //!<  uses when playing
    byte buffer;     //!<  value sometime used to prevent bug on change
    byte min;        //!<  min value often 0
    byte max;        //!<  max value
    byte cursor_pos; //!<  on screen from 0 to 63
} parameter;

/**
 * @brief 5 output set HIGH by default.
 *
 * @remark NPN switching output.
 */
void pin_init();

/**
 * @brief At start the led turn on from left to right.
 *
 * If there is a bug, the led turn off.
 */
void pin_test();
#endif
