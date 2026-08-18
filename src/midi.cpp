/**
 * @file midi.cpp
 * @brief Gestion des messages MIDI.
 */

#include <MIDI.h>
#include "midi.h"
#include "Modules.h"

extern Modules *myModules;
using namespace MIDI_NAMESPACE;
extern MidiInterface<SerialMIDI<HardwareSerial>> MIDI; /**<interface MIDI*/


/**
 * @brief Gestion note on de la librairie
 * 
 * On renvoie à tous les modules
 */

void handleNoteOn(byte channel, byte pitch, byte velocity) {
    for(int i = 3; i < 6; i++) {
        myModules->modules[i]->handleNoteOn(
            channel, pitch, velocity);
    }
}

/**
 * @brief Gestion note off de la librairie
 * 
 * On renvoie à tous les modules
 */

void handleNoteOff(byte channel, byte pitch, byte velocity) {
    for(int i = 3; i < 6; i++) {
        myModules->modules[i]->handleNoteOff(
            channel, pitch, velocity);
    }
}

void handleClock() {
    myModules->modules[TIME]->handleClock();
}

void handleStart() {
    myModules->modules[TIME]->handleStart();
}

void handleStop() {
    myModules->modules[TIME]->handleStop();    
}

