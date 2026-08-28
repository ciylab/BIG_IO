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
