/**
 * @file gate.cpp
 */

#include "gate.h"

void pin_init() {
    pinMode(CLK1, INPUT_PULLUP);
    pinMode(DT1, INPUT_PULLUP);
    pinMode(SW1, INPUT_PULLUP);
    pinMode(CLK2, INPUT_PULLUP);
    pinMode(DT2, INPUT_PULLUP);
    pinMode(SW2, INPUT_PULLUP);
#ifdef nanor4
    pinMode(LED, OUTPUT);
#elif bluepill
    pinMode(CLOCK_IN, INPUT);
#endif    
    for(int i = 0; i < 5; i++) {
        pinMode(gates[i], OUTPUT);
#ifdef nanor4
        digitalWrite(gates[i], LOW);
#elif bluepill
        digitalWrite(gates[i], HIGH);
#endif
    }
}

void gates_test() {
    for(int i = 0; i < 5; i++) {
        digitalWrite(gates[i], LOW);
        delay(100);
        digitalWrite(gates[i], HIGH);
    }
}
