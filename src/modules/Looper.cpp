/**
 * @file Looper.cpp
 */

#include <MIDI.h>
#include "../Time.h"
#include "../Modules.h"
#include "../dac.h"
#include "../encoder.h"
#include "../midi.h"
#include "Looper.h"

using namespace MIDI_NAMESPACE;
extern MidiInterface<SerialMIDI<HardwareSerial>> MIDI; /**<interface MIDI*/

void Looper::del() {
    memset(pitchOn, 0, 384);
    memset(pitchOff, 0, 384);
}

void Looper::startPlay() {
    // pour prévenir le changement de canal de sortie
    // mais pas totalement fiable !!!
    this->io[1].buffer = this->io[1].value;
    if(2 < this->io[1].value) {
        MIDI.sendNoteOn(pitchOn[index], 127, this->io[1].value - 2);
    }
    if(1 < this->io[3].value) {
        // pour prévenir un changement de gate
        this->io[3].buffer = this->io[3].value;
        digitalWrite(pins[this->io[3].value - 1], LOW);
    }
    if(this->io[2].value != 0) {        
        dac_write(this->io[2].value - 1, pitchOn[index]); 
    }
}

void Looper::stopPlay() {
    if(2 < this->io[1].buffer) {
        MIDI.sendNoteOff(pitchOff[index], 0, this->io[1].buffer - 2);
    }
    if(1 < this->io[3].buffer) {
        digitalWrite(pins[this->io[3].buffer - 1], HIGH);
    }            
}


void Looper::execute() {
    if(this->parameters[0].value == 0) {
        return ;
    }
    if(Time::newTick) {
        this->index = Time::tick % (6 * this->parameters[0].value);
        if(this->pitchOn[index] != 0) {
            startPlay();
        } else if (this->pitchOff[index] != 0) {
            stopPlay();
        }
    }
}

void Looper::l_handlePress() {
    Modules::current = PLAY; 
    Display::newPage();
}

void Looper::r_handlePress() {
    if(Display::cursor_num == 2) {
        if(this->parameters[2].value == 1) {
            r_handleRotate(-1);
        } else {
            r_handleRotate(1);
        }
    } else if(Display::cursor_num == 3) {
        del();
        r_handleRotate(0);
    }
}

void Looper::handleNoteOn(byte channel, byte pitch, byte velocity) {
    if(channel != this->io[0].value - 2) {
        return;
    }
    MIDI.sendNoteOn(pitch, velocity, this->io[1].value - 2);
    if(this->parameters[2].value) { // record on
        // pour prévenir un arrêt de l'enregistrement alors
        // qu'une note est jouée.
        this->parameters[2].buffer = this->parameters[2].value;
        if(this->parameters[1].value) { // RT
            pitchOn[Time::tick % (6 * this->parameters[0].value)] = pitch;
        } else { // step by step
            pitchOn[6 * stepIndex] = pitch;
            pitchOff[6 * stepIndex + this->parameters[4].value] = pitch;
            stepIndex = (stepIndex + 1) % this->parameters[0].value;
        }
    }
}

void Looper::handleNoteOff(byte channel, byte pitch, byte velocity) {
    if(channel != this->io[0].value - 2) {
        return;
    }
    MIDI.sendNoteOff(pitch, velocity, this->io[1].value - 2);
    if(!this->parameters[1].value) {
        return;
    }
    if(this->parameters[2].buffer && // record on
            this->parameters[1].value) { // RT
        pitchOff[Time::tick % (6 * this->parameters[0].value)] = pitch;
        this->parameters[2].buffer = 0;
    }
}

