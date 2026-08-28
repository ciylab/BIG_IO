/**
 * @file Modules.cpp
 */

/**
 * @brief The necessary modules.
 */

#include "Module.h"
#include "Main.h"
#include "Conf.h"
#include "Time.h"
#include "Play.h"
#include "Modules.h"
#include "io.h"

/**
 * @brief The available modules.
 */

#include "modules/Trigger.h"
#include "modules/Miniseq.h"
#include "modules/Random.h"
#include "modules/Simple.h"
#include "modules/Looper.h"

byte Modules::current = MAIN;
byte Modules::to_config = TIME;

Modules::Modules() {
    this->modules[0] = new Main();
    this->modules[1] = new Conf();
    this->modules[2] = new io();
    this->modules[3] = new Play();
    for (int i = TIME; i < TIME + 8; i++) {
        this->modules[i] = NULL;
    }
}

void Modules::execute() {
    for (int i = TIME; i < TIME + 8; i++) {
        this->modules[i]->execute();
    }
}

Module *Modules::getModule(byte num) {
    switch(num) {
        case 0:
            return new Time();
            break;
        case 1:
            return new Miniseq();
            break;
        case 2:
            return new Random();
            break;
        case 3:
            return new Simple();
            break;
        case 4:
            return new Trigger();
            break;
        case 5:
            return new Looper();
            break;
        default:
            return new Module();
    }
}

void Modules::load_module_from_memory(byte index, byte module_num) {
    Modules::to_config = module_num + TIME;
    if(this->modules[Modules::to_config] != NULL) {
        this->modules[Modules::to_config]->panic();     // clean midi out
        this->modules[Modules::to_config]->closeGate(); // no more gate
        Module::del(this->modules[Modules::to_config]); // free memory
    }
    this->modules[Modules::to_config] = Modules::getModule(index);
    this->modules[CONF]->parameters[module_num].value = index;
    // CONF and PLAY text page
    byte offsetInPage = 
        this->modules[CONF]->parameters[module_num].cursor_pos;
    for (int i = 0; i < 4; i++) {
        this->modules[CONF]->text[i + offsetInPage + 3] = 
            names[index][i];
        this->modules[PLAY]->text[i + offsetInPage + 3] = 
            names[index][i];
    }
}

