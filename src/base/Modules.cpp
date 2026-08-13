/**
 * @file Modules.cpp
 * @brief Gestion d'un module.
 */


#include "Module.h"
#include "Main.h"
#include "../time/Time.h"
#include "../trigger/Trigger.h"
#include "Play.h"
#include "Modules.h"

byte Modules::current = 0;
unsigned int Modules::C4RefVolt = 3277;

/**
 * @brief Constructeur par défaut.
 */

Modules::Modules() {
    this->size = 0;
    this->add(new Main("MAIN"));
    this->add(new Time("TIME"));
    this->add(new Play("PLAY"));
}

void Modules::add(Module *m) {
    modules[this->size] = m;
    this->size++;
}

/**
 * @brief Méthode principale.
 */

void Modules::execute() {
    /*
    for (int i = 0; i < size; i++) {
        this->modules[i]->execute();
    }*/
    this->modules[1]->execute(); // TIME
    this->modules[3]->execute(); // SIMPLE
    this->modules[4]->execute(); // TRIGGER
    this->modules[5]->execute(); // TRIGGER
    this->modules[6]->execute(); // MINISEQ
    //this->modules[9]->execute();
    //this->modules[9]->execute();
}

int Modules::getVoltage(byte pitch) {
    return min(4095, 
            (int) round(1. * pitch * Modules::C4RefVolt / 48));
}

