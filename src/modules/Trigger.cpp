/**
 * @file Trigger.cpp
 */
#include <MIDI.h>
#include "../Time.h"
#include "Trigger.h"
#include "../Modules.h"
#include "../midi.h"
#include "../encoder.h"

using namespace MIDI_NAMESPACE;
extern MidiInterface<SerialMIDI<HardwareSerial>> MIDI;

bool Trigger::isPulse() {
    byte length = parameters[0].value;
    if ((parameters[2].value *
                (length - parameters[3].value + Time::tick / 6)) % length < 
            parameters[2].value) {
        return true;
    }
    if ((parameters[4].value *
                (length - parameters[5].value + Time::tick / 6)) % length < 
            parameters[4].value) {
        return true;
    }
    return false;
}

void Trigger::startPlay(byte pitch) {
    parameters[6].buffer = pitch;
    startPlayMIDI(pitch);
    startPlayGate();
}

void Trigger::stopPlay(byte pitch) {
    stopPlayMIDI(pitch);
    stopPlayGate();
}

void Trigger::execute() {
    if (parameters[0].value == 0 ||
            (parameters[2].value == 0 && parameters[3].value == 0)) {
        return;
    }
    if(Time::newTick) {
        if(Time::tick % 6 == 0 && isPulse()) {
            startPlay(parameters[6].value);
            start = Time::tick;
        } else if (Time::tick == start + parameters[1].value) {
            stopPlay(parameters[6].buffer);
        }
    }
}

void Trigger::l_handlePress() {
    Modules::current = PLAY; 
    Display::newPage();
}

void Trigger::r_handlePress() {
}

