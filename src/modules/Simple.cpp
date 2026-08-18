/**
 * @file Simple.cpp
 */

#include <MIDI.h>
#include "../Time.h"
#include "../Modules.h"
#include "../dac.h"
#include "Simple.h"

using namespace MIDI_NAMESPACE;
extern MidiInterface<SerialMIDI<HardwareSerial>> MIDI; /**<interface MIDI*/

bool Simple::isInRange(byte pitch) {
    return this->parameters[4].value <= pitch &&
        pitch < this->parameters[5].value;
}

void Simple::handleNoteOn(byte channel, byte pitch, byte velocity) {
    if(!isInRange(pitch) || channel != this->parameters[0].value) {
        return;
    }
    if(this->parameters[1].value != 0) {
        // pour prévenir un éventuel changement de sortie midi
        // en cours de jeu... limité à une note !!!
        this->parameters[1].buffer = this->parameters[1].value;
        // pour prévenir un éventuel changement de transposition 
        // en cours de jeu.
        pitch_send[pitch] = pitch + this->parameters[6].value;
        MIDI.sendNoteOn(pitch_send[pitch],
                velocity, this->parameters[1].buffer);
    }
    if(this->parameters[2].value != 0) {
        digitalWrite(pins[parameters[2].value], LOW);
    }
    if(this->parameters[3].value != 0) {
        dac_write(this->parameters[3].value - 1, 
                Modules::getVoltage(pitch));
    }
}

void Simple::handleNoteOff(byte channel, byte pitch, byte velocity) {
    if(!isInRange(pitch) || channel != this->parameters[0].value) {
        return;
    }
    if(this->parameters[1].buffer != 0) {
        MIDI.sendNoteOff(pitch_send[pitch], 0, 
                this->parameters[1].buffer);
    }
    if(this->parameters[2].value != 0) {
        digitalWrite(pins[parameters[2].value], HIGH);
    }
}

void Simple::l_handlePress() {
    Modules::current = PLAY; 
    Display::newPage();
}

void Simple::r_handlePress() {}

