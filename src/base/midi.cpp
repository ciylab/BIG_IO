/**
 * @file midi.cpp
 * @brief Gestion des messages MIDI.
 */

#include "midi.h"
#include "Modules.h"

extern Modules *myModules;

/**
 * @brief Gestion note on de la librairie
 * 
 * On renvoie à tous les modules
 */

void handleNoteOn(byte channel, byte pitch, byte velocity) {
}

/**
 * @brief Gestion note off de la librairie
 * 
 * On renvoie à tous les modules
 */

void handleNoteOff(byte channel, byte pitch, byte velocity) {
}

void handleClock() {
    myModules->modules[1]->handleClock();
}

void handleStart() {
    myModules->modules[1]->handleStart();
}

void handleStop() {
    myModules->modules[1]->handleStop();    
}

