/**
 * @file config.cpp
 * @brief Fichier de configuration du projet.
 */

#include "config.h"

void pin_init() {
    pinMode(CLOCK_IN, INPUT);
    pinMode(PA0, INPUT_PULLUP);
    pinMode(PA1, INPUT_PULLUP);
    pinMode(PA2, INPUT_PULLUP);
    pinMode(PB0, INPUT_PULLUP);
    pinMode(PB1, INPUT_PULLUP);
    pinMode(PB10, INPUT_PULLUP);
    for(int i = 0; i < 5; i++) {
        pinMode(pins[i], OUTPUT);
        digitalWrite(pins[i], HIGH);
    }
}

void pin_test() {
    for(int i = 0; i < 5; i++) {
        digitalWrite(pins[i], LOW);
        delay(100);
        digitalWrite(pins[i], HIGH);
    }
}
