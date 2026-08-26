/**
 * @file Module.cpp
 * @brief Gestion d'un module.
 *
 * Un module est un algorithme qui traite les données MIDI
 * et gère l'encodeur VALUE
 */

#include "Module.h"

char *names[7] = {
    "TIME  ", "BASS  ", "RANDOM", "REDIR ", "DRUM  ", "SEQ   ", "NONE"
};

/**
 * @brief Constructeur.
 */

Module::Module() {
    size = 0;
    indexInList = 6;
    new_value = false;
    for (int i = 0; i < TEXT_SIZE; i++) {
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
}

void Module::r_handlePress() {
}


