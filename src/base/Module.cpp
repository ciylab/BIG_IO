/**
 * @file Module.cpp
 * @brief Gestion d'un module.
 *
 * Un module est un algorithme qui traite les données MIDI
 * et gère l'encodeur VALUE
 */


#include "Module.h"
#include "Modules.h"

/**
 * @brief Constructeur.
 */

Module::Module() {
    size = 0;
}

/**
 * @brief Constructeur avec initialisation des paramètres.
 */

Module::Module(char *name) {
    size = 0;
    strcpy(this->name, name);
    for (int i = 0; i < 64; i++) {
        text[i] = ' ';
    }
}

void Module::add(parameter p) {
    parameters[size] = p;
    size++;
}

/**
 * @brief Menu spécifique au module.
 */

void Module::setMenu() {
    byte offset;
    for (int i = 0; i < size; i++) {
        offset = parameters[i].cursor_pos;
        for (int j = 0; j < 7; j++) {
            text[j + offset] = parameters[i].name[j];
        }
    }
}

void Module::l_handlePress() {
    Modules::current = MAIN; 
    Display::newPage();
}


