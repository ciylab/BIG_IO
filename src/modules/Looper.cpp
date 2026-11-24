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

void Looper::read_sequence() {
    if(parameters[5].value == 0) {
        return;
    }
    byte mem_num = parameters[5].value - 1;
    byte length;
    unsigned int offset = 8 * CONFIG_SIZE * NUM_SLOT;
    offset += mem_num * (1 + 3 * 16 * 6 * N_BARS);
    length = readEEPROM(offset++);
    for(int i = 0; i < 6 * length; i++) {
        pitchOn[i] = readEEPROM(offset++);
        velocities[i] = readEEPROM(offset++);
        pitchOff[i] = readEEPROM(offset++);
    }
    parameters[0].value = length;
}

void Looper::write_sequence() {
    if(parameters[6].value == 0) {
        return;
    }
    byte mem_num = parameters[6].value - 1;
    byte length = parameters[0].value;
    unsigned int offset = 8 * CONFIG_SIZE * NUM_SLOT;
    offset += mem_num * (1 + 3 * 16 * 6 * N_BARS);
    updateEEPROM(offset++, length);
    for(int i = 0; i < 6 * length; i++) {
        updateEEPROM(offset++, pitchOn[i]);
        updateEEPROM(offset++, velocities[i]);
        updateEEPROM(offset++, pitchOff[i]);
    }
}

void Looper::del_seq() {
    for(int i = 0; i < 6 * this->parameters[0].value; i++) {
        if(this->pitchOn[i] != 0) {
            MIDI.sendNoteOff(this->pitchOn[i], 0, this->io[1].value);
        }
    }
    memset(pitchOn, 0, 96 * N_BARS);
    memset(pitchOff, 0, 96 * N_BARS);
    memset(velocities, 0, 96 * N_BARS);
}

void Looper::startPlay(byte pitch, byte velocity) {
    if(ns.isEmpty()) {
        startPlayGate();
    }
    ns.push(pitch);
    startPlayMIDI(pitch, velocity);
    startPlayCV(pitch);
}

void Looper::stopPlay(byte pitch) {
    ns.remove(pitch);
    stopPlayMIDI(pitch);
    if(ns.isEmpty()) {
        stopPlayGate();
    } else {
        startPlayCV(ns.top());
    }
}

void Looper::execute() {
    if(this->parameters[0].value == 0) {
        return ;
    }
    if(Time::newTick) {
        this->index = Time::tick % (6 * this->parameters[0].value);
        if(this->pitchOn[this->index] != 0) {
            startPlay(this->pitchOn[index], this->velocities[index]);
        } 
        if (this->pitchOff[index] != 0) {
            stopPlay(this->pitchOff[index]);
        }
    }
}

void Looper::l_handlePress() {
    Modules::current = PLAY; 
    Display::newPage();
}

void Looper::r_handlePress() {
    if(Display::cursor_num == 3) {        // record
        this->new_value = true;
        Display::show_value(this->parameters[3].value); 
        temp = 1 - this->parameters[3].value; 
    } else if(Display::cursor_num == 4) { // delete
        del_seq();
        r_handleRotate(0);
    } else if(this->new_value && Display::cursor_num == 5) { // load
        this->read_sequence();
        Display::print_here(" LOADED");
    } else if(this->new_value && Display::cursor_num == 6) { // save
        this->write_sequence();
        Display::print_here(" SAVED");
    }
}

void Looper::handleNoteOn(byte channel, byte pitch, byte velocity) {
    if(channel != this->io[0].value) {
        return;
    }
    startPlay(pitch, velocity);
    if(this->parameters[3].value) { // record on
        this->parameters[3].buffer = this->parameters[3].value;
        if(this->parameters[2].value) { // RT
            index = Time::tick % (6 * this->parameters[0].value);
        } else { // step by step
            index = 6 * stepIndex;
            pitchOff[index + this->parameters[1].value] = pitch;
            stepIndex = (stepIndex + 1) % this->parameters[0].value;
        }
        pitchOn[index] = pitch;
        velocities[index] = velocity;
    }
}

void Looper::handleNoteOff(byte channel, byte pitch, byte velocity) {
    if(channel != this->io[0].value) {
        return;
    }
    stopPlay(pitch);
    if(!this->parameters[2].value) {
        return;
    }
    if(this->parameters[3].buffer &&  // record on
            this->parameters[2].value // RT
      ) {
        pitchOff[Time::tick % (6 * this->parameters[0].value)] = pitch;
    }
}

