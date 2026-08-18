/**
 * @file Modules.cpp
 * @brief Gestion d'un module.
 */

/**
 * @brief Les modules de base.
 */

#include "Module.h"
#include "Main.h"
#include "Time.h"
#include "Play.h"
#include "Modules.h"

/**
 * @brief Les modules disponibles.
 */

#include "modules/Trigger.h"
#include "modules/Miniseq.h"
#include "modules/Random.h"
#include "modules/Simple.h"

byte Modules::current = 0;
unsigned int Modules::C4RefVolt = 3277;

/**
 * @brief Constructeur par défaut.
 */

Modules::Modules() {
    this->modules[0] = new Main();
    this->modules[1] = new Play();
}

/**
 * @brief Méthode principale.
 */

void Modules::execute() {
    for (int i = 2; i < 10; i++) {
        this->modules[i]->execute();
    }
}

int Modules::getVoltage(byte pitch) {
    return min(4095, 
            (int) round(1. * pitch * Modules::C4RefVolt / 48));
}

Module *Modules::getModule(byte num) {
    switch(num) {
        case 1:
            return new Time();
            break;
        case 2:
            return new Miniseq();
            break;
        case 3:
            return new Random();
            break;
        case 4:
            return new Simple();
            break;
        case 5:
            return new Trigger();
            break;
        default:
            return new Module();
    }
}

