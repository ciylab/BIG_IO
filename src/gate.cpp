/**
 * @file gate.cpp
 */

#include "gate.h"

void pin_init() {
    pinMode(CLOCK_IN, INPUT);
    pinMode(CLK1, INPUT_PULLUP);
    pinMode(DT1, INPUT_PULLUP);
    pinMode(SW1, INPUT_PULLUP);
    pinMode(CLK2, INPUT_PULLUP);
    pinMode(DT2, INPUT_PULLUP);
    pinMode(SW2, INPUT_PULLUP);
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
