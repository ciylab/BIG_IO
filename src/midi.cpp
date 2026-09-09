/**
 * @file midi.cpp
 */

#include <MIDI.h>
#include "midi.h"
#include "Modules.h"

extern Modules *myModules;
using namespace MIDI_NAMESPACE;
extern MidiInterface<SerialMIDI<HardwareSerial>> MIDI;

void handleNoteOn(byte channel, byte pitch, byte velocity) {
    for(int i = TIME; i < 8 + TIME; i++) {
        myModules->modules[i]->handleNoteOn(
            channel, pitch, velocity);
    }
}

void handleNoteOff(byte channel, byte pitch, byte velocity) {
    for(int i = TIME; i < 8 + TIME; i++) {
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

void panic() {
    for(int i = TIME; i < 8 + TIME; i++) {
        myModules->modules[i]->panic();
    }
}

void clear_channel(byte channel) {
    for (byte pitch = 1; pitch <= 108; pitch++) {
        MIDI.sendNoteOff(pitch, 0, channel);
    }
}

void handleProgramChange(byte channel, byte number) {
    if(7 < number) {
        return;
    }
    Module *m = myModules->modules[number + TIME];
    if(m->size == 0) {
        return;
    }
    m->new_value = false;
    Modules::current = number + TIME;
    Display::newPage();
}

/**
 * Fonction qui modifie les paramètres par CC.
 */
void handleControlChange(byte channel, byte number, byte value) {
    Module *m = NULL;
    int i = TIME;
    while(i < TIME + 8) {
        m = myModules->modules[i];
        if(m->io[0].value == channel) {
            break;
        }
        i++;
    }
    if(i == TIME + 8) {
        return;
    }
    if(m->size + 1 < number) {
        return;
    }
    parameter *p = &(m->parameters)[number - 1];
    p->value = map(value, 0, 127, p->min, p->max);
    m->new_value = true;
}


