/**
 * @file Miniseq.cpp
 */

#include <MIDI.h>
#include "../Time.h"
#include "../Modules.h"
#include "../midi.h"
#include "../dac.h"
#include "../encoder.h"
#include "Miniseq.h"

using namespace MIDI_NAMESPACE;
extern MidiInterface<SerialMIDI<HardwareSerial>> MIDI; /**<interface MIDI*/

void Miniseq::startPlay(byte pitch) {
    if(count != 0) {
        return;
    }
    this->parameters[2 + noteIndex].buffer = pitch;
    startPlayMIDI(pitch);
    startPlayCV(pitch);
    startPlayGate();
}

void Miniseq::stopPlay(byte pitch) {
    if(count == 0) {
        stopPlayMIDI(pitch);
        stopPlayCV();
        stopPlayGate();
        noteIndex = (noteIndex + 1) % this->parameters[0].value; 
    }
    count = (count + 1) % this->parameters[7].value;
}

void Miniseq::execute() {
    if(this->parameters[0].value == 0) {
        return ;
    }
    if(Time::newTick) {
        if(Time::tick % 6 == 0) {
            startPlay(this->parameters[2 + noteIndex].value);
            start = Time::tick;
        } else if (Time::tick == start + this->parameters[1].value) {
            stopPlay(this->parameters[2 + noteIndex].buffer);
        }
    }
}

void Miniseq::l_handlePress() {
    Modules::current = PLAY; 
    Display::newPage();
}

void Miniseq::r_handlePress() {
}
