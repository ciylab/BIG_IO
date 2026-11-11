/**
 * @file pin.cpp
 */

#include "pin.h"

void pin_init() {
    pinMode(CLK1, INPUT_PULLUP);
    pinMode(DT1, INPUT_PULLUP);
    pinMode(SW1, INPUT_PULLUP);
    pinMode(CLK2, INPUT_PULLUP);
    pinMode(DT2, INPUT_PULLUP);
    pinMode(SW2, INPUT_PULLUP);
    pinMode(CLOCK_IN, INPUT_PULLUP);
    for(int i = 0; i < 6; i++) {
        pinMode(gates[i], OUTPUT);
#ifdef nanor4
        digitalWrite(gates[i], LOW);
#elif bluepill
        digitalWrite(gates[i], HIGH);
#endif
    }
#ifdef bluepill
    digitalWrite(LED, LOW);
#endif
}

