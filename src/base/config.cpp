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
#include "../trigger/Trigger.h"
#include "../simple/Simple.h"

parameter values[16][8];
algo algos[8];
extern Modules *myModules;

char *actions[8] = {
    "NONE  ", // 0
    "ARPEG ", // 1
    "COMP  ", // 2
    "MINISQ", // 3
    "RAND  ", // 0
    "RECORD", // 5
    "SIMPLE", // 6
    "TRIG  "  // 7
};

void load_modules() {
    Module *m;
    byte offset;
    for(int i = 0; i < 8; i++) {
        switch(algos[i].action) {
            case 1:
                m = new Module("ARPEG");
                break;
            case 2:
                m = new Module("COMP");
                break;
            case 3:
                m = new Module("MINISQ");
                break;
            case 4:
                m = new Module("RAND");
                break;
            case 5:
                m = new Module("RECORD");
                break;
            case 6:
                m = new Simple(actions[6]);
                break;
            case 7:
                m = new Trigger(actions[7]);
                break;
            default:
                m = new Module(actions[0]);
                break;
        }
        myModules->add(m);
        myModules->modules[2]->parameters[i].value = algos[i].action;
        myModules->modules[2]->parameters[i].buffer = algos[i].action;
        offset = myModules->modules[2]->parameters[i].cursor_pos;
        for (int j = 0; j < 4; j++) {
            myModules->modules[2]->text[j + offset + 3] = 
                myModules->modules[i + 3]->name[j];
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
        delay(100);
        digitalWrite(pins[i], HIGH);
    }
}
