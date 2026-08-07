/**
 * @file config.cpp
 * @brief Fichier de configuration du projet.
 */

#include "config.h"
#include "Module.h"
#include "Display.h"

parameter values[16][8];
algo algos[8];
Module modules[3];
extern char *actions[8];

void update_algo() {
    byte offset;
    for(int i = 0; i < 8; i++) {
        modules[2].parameters[i].value = algos[i].action;
        modules[2].parameters[i].buffer = algos[i].action;
        offset = modules[2].parameters[i].cursor_pos;
        for (int j = 0; j < 4; j++) {
            modules[2].text[j + offset + 3] = actions[algos[i].action][j];
        }
    }
}

void init_modules() {
    modules[0] = Module("MAIN");
    modules[0].add({" TIME  ", 0, 0, 0, 0, 0});
    modules[0].add({" CALIBR", 128, 128, 0, 255, 16});
    modules[0].add({" PLAY  ", 0, 0, 0, 7, 32});
    modules[0].add({" LOAD  ", 0, 0, 0, 7, 48});
    modules[0].add({" SAVE  ", 1, 1, 1, 7, 56});
    modules[0].setMenu();
    modules[1] = Module("TIME");
    modules[1].add({" IN    ", 0, 0, 0, 2, 0});
    modules[1].add({" OUT   ", 0, 0, 0, 22, 16});
    modules[1].add({" BPM   ", 60, 60, 30, 250, 32});
    modules[1].setMenu();
    modules[2] = Module("PLAY");
    modules[2].add({" 1:    ", 0, 0, 0, 7, 0});
    modules[2].add({" 2:    ", 0, 0, 0, 7, 8});
    modules[2].add({" 3:    ", 0, 0, 0, 7, 16});
    modules[2].add({" 4:    ", 0, 0, 0, 7, 24});
    modules[2].add({" 5:    ", 0, 0, 0, 7, 32});
    modules[2].add({" 6:    ", 0, 0, 0, 7, 40});
    modules[2].add({" 7:    ", 0, 0, 0, 7, 48});
    modules[2].add({" 8:    ", 0, 0, 0, 7, 56});
    modules[2].setMenu();
}

