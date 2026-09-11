/**
 * @file Looper.cpp
 */

#include <MIDI.h>
#include "../Time.h"
#include "../Modules.h"
#include "../dac.h"
#include "../encoder.h"
#include "../midi.h"
#include "../eeprom.h"
#include "Looper.h"

using namespace MIDI_NAMESPACE;
extern MidiInterface<SerialMIDI<HardwareSerial>> MIDI; /**<interface MIDI*/

void Looper::del_seq() {
    memset(pitchOn, 0, 384);
    memset(pitchOff, 0, 384);
    memset(velocities, 0, 384);
}

bool Looper::getData(int index, byte data[6]) {
    data[0] = pitchOn[index];
    if(data[0] == 0) {
        return false;
    }
    data[1] = velocities[index];
    data[2] = index >> 8;
    data[3] = index & 0xFF;
    while(pitchOff[index] != data[0]) {
        index = (index + 1) % (6 * parameters[0].value);
    }
    data[4] = index >> 8;
    data[5] = index & 0xFF;
    return true;
}

void Looper::startPlay(byte pitch, byte velocity) {
    startPlayMIDI(pitch, velocity);
    startPlayCV(pitch);
    startPlayGate();
}

void Looper::stopPlay(byte pitch) {
    stopPlayMIDI(pitch);
    stopPlayCV();
    stopPlayGate();
}

void Looper::execute() {
    if(this->parameters[0].value == 0) {
        return ;
    }
    if(Time::newTick) {
        this->index = Time::tick % (6 * this->parameters[0].value);
        if(this->pitchOn[index] != 0) {
            startPlay(this->pitchOn[index], this->velocities[index]);
        } else if (this->pitchOff[index] != 0) {
            stopPlay(this->pitchOff[index]);
        }
    }
}

void Looper::l_handlePress() {
    Modules::current = PLAY; 
    Display::newPage();
}

void Looper::r_handlePress() {
    if(Display::cursor_num == 2) {
        this->new_value = true;
        Display::show_value(this->parameters[2].value); 
        temp = 1 - this->parameters[2].value; 
    } else if(Display::cursor_num == 3) {
        del_seq();
        count = 0;
        r_handleRotate(0);
    }
}

void Looper::handleNoteOn(byte channel, byte pitch, byte velocity) {
    if(channel != this->io[0].value) {
        return;
    }
    startPlayMIDI(pitch, velocity);
    startPlayCV(pitch);
    startPlayGate();
    if(this->parameters[2].value) { // record on
        this->parameters[2].buffer = this->parameters[2].value;
        if(this->parameters[1].value && count < NUM_NOTES) { // RT
            pitchOn[Time::tick % (6 * this->parameters[0].value)] = pitch;
            velocities[Time::tick % (6 * this->parameters[0].value)] =
                velocity;
        } else { // step by step
            pitchOn[6 * stepIndex] = pitch;
            velocities[6 * stepIndex] = velocity;
            pitchOff[6 * stepIndex + this->parameters[4].value] = pitch;
            stepIndex = (stepIndex + 1) % this->parameters[0].value;
        }
    }
}

void Looper::handleNoteOff(byte channel, byte pitch, byte velocity) {
    if(channel != this->io[0].value) {
        return;
    }
    stopPlayMIDI(pitch);
    stopPlayCV();
    stopPlayGate();
    if(!this->parameters[1].value) {
        return;
    }
    if(this->parameters[2].buffer && // record on
            this->parameters[1].value && // RT
            count < NUM_NOTES) {
        pitchOff[Time::tick % (6 * this->parameters[0].value)] = pitch;
        this->parameters[2].buffer = 0;
        count++;
    }
}

