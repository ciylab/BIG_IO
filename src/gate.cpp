/**
 * @file gate.cpp
 */

#include "gate.h"

void pin_init() {
    pinMode(CLOCK_IN, INPUT);
    pinMode(PA0, INPUT_PULLUP);
    pinMode(PA1, INPUT_PULLUP);
    pinMode(PA2, INPUT_PULLUP);
    pinMode(PB0, INPUT_PULLUP);
    pinMode(PB1, INPUT_PULLUP);
    pinMode(PB10, INPUT_PULLUP);
    for(int i = 0; i < 5; i++) {
        pinMode(gates[i], OUTPUT);
        digitalWrite(gates[i], HIGH);
    }
}

void gates_test() {
    for(int i = 0; i < 5; i++) {
        digitalWrite(gates[i], LOW);
        delay(100);
        digitalWrite(gates[i], HIGH);
    }
}
