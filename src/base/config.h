#ifndef CONFIG_H
#define CONFIG_H
#include <Arduino.h>

typedef struct data {
    byte val;
    byte min;
    byte max;
    byte buffer;
} data;

typedef struct algo {
    byte in;
    byte out;
    byte action_num;
} algo;

void init_data();
#endif
