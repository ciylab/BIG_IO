/**
 * @file config.cpp
 * @brief Fichier de configuration du projet.
 */

#include "config.h"
#include "Module.h"
#include "Modules.h"
#include "Display.h"
#include "Main.h"
#include "Play.h"
#include "../time/Time.h"

parameter values[16][8];
algo algos[8];
extern Modules *myModules;

char *actions[8] = {
    "NONE  ", // 0
    "ARPEG ", // 1
    "COMP  ", // 2
    "MINISQ", // 3
    "RAND  ", // 4
    "RECORD", // 5
    "SIMPLE", // 6
    "TRIG  "  // 7
};

void update_algo() {
    byte offset;
    for(int i = 0; i < 8; i++) {
        myModules->modules[2]->parameters[i].value = algos[i].action;
        myModules->modules[2]->parameters[i].buffer = algos[i].action;
        offset = myModules->modules[2]->parameters[i].cursor_pos;
        for (int j = 0; j < 4; j++) {
            myModules->modules[2]->text[j + offset + 3] = 
                actions[algos[i].action][j];
        }
    }
}

void pin_init() {
    for(int i = 0; i < 5; i++) {
        pinMode(pins[i], OUTPUT);
        digitalWrite(pins[i], HIGH);
    }
}

void pin_test() {
    for(int i = 0; i < 5; i++) {
        digitalWrite(pins[i], LOW);
        delay(500);
        digitalWrite(pins[i], HIGH);
    }
}
