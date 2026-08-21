/**
 * @file Modules.cpp
 * @brief Gestion d'un module.
 */

/**
 * @brief Les modules de base.
 */

#include "Module.h"
#include "Main.h"
#include "Conf.h"
#include "Time.h"
#include "Play.h"
#include "Modules.h"
#include "io.h"

/**
 * @brief Les modules disponibles.
 */

#include "modules/Trigger.h"
#include "modules/Miniseq.h"
#include "modules/Random.h"
#include "modules/Simple.h"

byte Modules::current = MAIN;
byte Modules::to_config = MAIN;

unsigned int Modules::C4RefVolt = 3277;

/**
 * @brief Constructeur par défaut.
 */

Modules::Modules() {
    this->modules[0] = new Main();
    this->modules[1] = new Conf();
    this->modules[2] = new io();
    this->modules[3] = new Play();
}

/**
 * @brief Méthode principale.
 */

void Modules::execute() {
    for (int i = TIME; i < TIME + 8; i++) {
        this->modules[i]->execute();
    }
}

int Modules::getVoltage(byte pitch) {
    return min(4095, 
            (int) round(1. * pitch * Modules::C4RefVolt / 48));
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
        default:
            return new Module();
    }
}

