#ifndef CONFIG_H
#define CONFIG_H
#include <Arduino.h>


#define CLOCK_IN PA3
#define CLOCK_OUT PB3
#define GATE_1 PB5
#define GATE_2 PB4
#define DRUM_2 PB8
#define DRUM_1 PB9


#define MAIN 0
#define TIME 1
#define PLAY 2

const byte pins[] = {
    CLOCK_OUT, DRUM_1, DRUM_2, GATE_1, GATE_2};

typedef struct parameter {
    char name[8];    // name to display
    byte value;      // uses when playing
    byte buffer;     // value before update to prevent change when note on
    byte min;        // min value
    byte max;        // max value
    byte cursor_pos; // on screen from 0 to 63
} parameter;

typedef struct algo {
    byte in;
    byte out;
    byte action;
} algo;

void load_modules();
void pin_init();
void pin_test();
#endif
