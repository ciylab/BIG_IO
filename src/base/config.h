#ifndef CONFIG_H
#define CONFIG_H
#include <Arduino.h>

#define MAIN 0
#define TIME 1
#define PLAY 2

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

void init_modules();
void update_algo();

#endif
