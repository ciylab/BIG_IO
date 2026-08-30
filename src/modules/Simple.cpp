/**
 * @file Simple.cpp
 */

#include <MIDI.h>
#include "../Time.h"
#include "../Modules.h"
#include "../midi.h"
#include "../dac.h"
#include "Simple.h"

using namespace MIDI_NAMESPACE;
extern MidiInterface<SerialMIDI<HardwareSerial>> MIDI; 
bool Simple::isInRange(byte pitch) {
    return this->parameters[0].value <= pitch &&
        pitch < this->parameters[1].value;
}

void Simple::handleNoteOn(byte channel, byte pitch, byte velocity) {
    if(!isInRange(pitch) || channel != this->io[0].value) {
        return;
    }
    pitch_send[pitch] = pitch + this->parameters[2].value;
    startPlayMIDI(pitch_send[pitch]);
    startPlayCV(pitch_send[pitch]);
    startPlayGate();
}

void Simple::handleNoteOff(byte channel, byte pitch, byte velocity) {
    if(!isInRange(pitch) || channel != this->io[0].value) {
        return;
    }
    stopPlayMIDI(pitch_send[pitch]);
    stopPlayCV(pitch_send[pitch]);
    stopPlayGate();
}

void Simple::l_handlePress() {
    Modules::current = PLAY; 
    Display::newPage();
}

void Simple::r_handlePress() {}

