/**
 * @file Miniseq.cpp
 */

#include <MIDI.h>
#include "../Time.h"
#include "../Modules.h"
#include "../dac.h"
#include "../encoder.h"
#include "Miniseq.h"

using namespace MIDI_NAMESPACE;
extern MidiInterface<SerialMIDI<HardwareSerial>> MIDI; /**<interface MIDI*/

void Miniseq::panic() {
    if(2 < this->io[1].value) {
        for (byte pitch = 1; pitch <= 108; pitch++) {
            MIDI.sendNoteOff(pitch, 0, this->io[1].value - 2);
        }
        this->io[1].value = 2;
    }
}

void Miniseq::startPlay() {
    if(2 < this->io[1].value) {
        // pour prévenir le changement de note
        this->parameters[2 + noteIndex].buffer =
            this->parameters[2 + noteIndex].value;
        // pour prévenir l'absence de note off
        this->io[1].buffer = this->io[1].value;
        MIDI.sendNoteOn(this->parameters[2 + noteIndex].value, 
                127, this->io[1].buffer - 2);
    }
    if(1 < this->io[3].value) {
        this->io[3].buffer = this->io[3].value;
        digitalWrite(pins[this->io[3].value - 1], LOW);
    }
    if(this->io[2].value != 0) {        
        dac_write(this->io[2].value - 1, 
                Modules::getVoltage(this->parameters[2 + noteIndex].value));
    }
}

void Miniseq::stopPlay() {
    if(2 < this->io[1].buffer) {
        MIDI.sendNoteOff(this->parameters[2 + noteIndex].buffer, 
                0, this->io[1].buffer - 2);
    }
    if(1 < this->io[3].buffer) {
        digitalWrite(pins[this->io[3].buffer - 1], HIGH);
    }            
    noteIndex = (noteIndex + 1) % this->parameters[0].value; 
}

void Miniseq::execute() {
    if(this->parameters[0].value == 0) {
        return ;
    }
    if(Time::newTick) {
        if(Time::tick % 6 == 0) {
            startPlay();
            start = Time::tick;
        } else if (Time::tick == start + this->parameters[1].value) {
            stopPlay();
        }
    }
}

void Miniseq::l_handlePress() {
    Modules::current = PLAY; 
    Display::newPage();
}

void Miniseq::r_handlePress() {
}
