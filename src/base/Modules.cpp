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
unsigned int Modules::c4_reference_voltage = 3277;

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
    this->modules[1]->execute();
    this->modules[3]->execute();
    this->modules[4]->execute();
    this->modules[5]->execute();
}

