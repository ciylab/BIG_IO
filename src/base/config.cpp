/**
 * @file config.cpp
 * @brief Fichier de configuration du projet.
 */

#include "config.h"
#include "Module.h"
#include "Display.h"
#include "Main.h"
#include "Play.h"
#include "../time/Time.h"

parameter values[16][8];
algo algos[8];

Module *modules[3];

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
        modules[2]->parameters[i].value = algos[i].action;
        modules[2]->parameters[i].buffer = algos[i].action;
        offset = modules[2]->parameters[i].cursor_pos;
        for (int j = 0; j < 4; j++) {
            modules[2]->text[j + offset + 3] = actions[algos[i].action][j];
        }
    }
}

void init_modules() {
    modules[0] = new Main("MAIN");
    modules[1] = new Time("TIME");
    modules[2] = new Play("PLAY");
}

