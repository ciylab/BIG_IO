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
extern MidiInterface<SerialMIDI<HardwareSerial>> MIDI; /**<interface MIDI*/

bool Simple::isInRange(byte pitch) {
    return this->parameters[0].value <= pitch &&
        pitch < this->parameters[1].value;
}

void Simple::panic() {
    if(2 < this->io[1].value) {
        clear_channel(this->io[1].value - 2);
        this->io[1].value = 2;
    }
}

void Simple::handleNoteOn(byte channel, byte pitch, byte velocity) {
    if(!isInRange(pitch) || channel != this->io[0].value - 2) {
        return;
    }
    // pour prévenir un éventuel changement de sortie midi
    // en cours de jeu... limité à une note !!!
    this->io[1].buffer = this->io[1].value;
    if(2 < this->io[1].value) {
        // pour prévenir un éventuel changement de transposition 
        // en cours de jeu.
        pitch_send[pitch] = pitch + this->parameters[2].value;
        MIDI.sendNoteOn(pitch_send[pitch],
                velocity, this->io[1].value - 2);
    }
    if(1 < this->io[3].value) {
        this->io[3].buffer = this->io[3].value;
        digitalWrite(pins[this->io[3].value - 1], LOW);
    }
    if(this->io[2].value != 0) {
        dac_write(this->io[2].value - 1, 
                Modules::getVoltage(pitch));
    }
}

void Simple::handleNoteOff(byte channel, byte pitch, byte velocity) {
    if(!isInRange(pitch) || channel != this->io[0].value - 2) {
        return;
    }
    if(2 < this->io[1].buffer) {
        MIDI.sendNoteOff(pitch_send[pitch], 0, this->io[1].buffer - 2);
    }
    if(1 < this->io[3].buffer) {
        digitalWrite(pins[this->io[3].buffer - 1], HIGH);
    }
}

void Simple::l_handlePress() {
    Modules::current = PLAY; 
    Display::newPage();
}

void Simple::r_handlePress() {}

