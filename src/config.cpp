/**
 * @file config.cpp
 * @brief Fichier de configuration du projet.
 */

#include "config.h"
// TODO : mettre la suite des include dans config.h ? 

void pin_init() {
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
