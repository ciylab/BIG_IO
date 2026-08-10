/**
 * @file Modules.cpp
 * @brief Gestion d'un module.
 */


#include "Module.h"
#include "Main.h"
#include "../time/Time.h"
#include "Play.h"
#include "Modules.h"

byte Modules::current = 0;

/**
 * @brief Constructeur par défaut.
 */

Modules::Modules() {
    this->size = 0;
}

void Modules::add(Module *m) {
    modules[this->size] = m;
    this->size++;
}

/**
 * @brief Méthode principale.
 */

void Modules::execute() {
    for (int i = 0; i < size; i++) {
        this->modules[i]->execute();
    }
}

