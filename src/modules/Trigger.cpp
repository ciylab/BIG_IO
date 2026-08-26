/**
 * @file Trigger.cpp
 * @brief Gestion du temps.
 */
#include <MIDI.h>
#include "../Time.h"
#include "Trigger.h"
#include "../Modules.h"
#include "../midi.h"
#include "../encoder.h"

using namespace MIDI_NAMESPACE;
extern MidiInterface<SerialMIDI<HardwareSerial>> MIDI; /**<interface MIDI*/

bool Trigger::isPulse() {
    byte length = parameters[0].value;
    if ((parameters[2].value *
                (length - parameters[3].value + Time::tick / 6)) % length < 
            parameters[2].value) {
        return true;
    }
    // idem pour la deuxième séquence
    if ((parameters[4].value *
                (length - parameters[5].value + Time::tick / 6)) % length < 
            parameters[4].value) {
        return true;
    }
    return false;
}

void Trigger::startPlay() {
    this->io[1].buffer = this->io[1].value;
    if(2 < this->io[1].value) {
        parameters[6].buffer = parameters[6].value;
        MIDI.sendNoteOn(parameters[6].buffer, 127, this->io[1].value - 2);
    }
    if(1 < this->io[3].value) {
        digitalWrite(pins[this->io[3].value - 1], LOW);
    }
}

void Trigger::stopPlay() {
    if(2 < this->io[1].buffer) {
        MIDI.sendNoteOff(parameters[6].buffer, 0, this->io[1].buffer - 2);
    }
    if(1 < this->io[3].value) {
        digitalWrite(pins[this->io[3].value - 1], HIGH);
    }
}

void Trigger::execute() {
    if (parameters[0].value == 0 ||
            (parameters[2].value == 0 && parameters[3].value == 0)) {
        return;
    }
    if(Time::newTick) {
        if(Time::tick % 6 == 0 && isPulse()) {
            startPlay();
            start = Time::tick;
        } else if (Time::tick == start + parameters[1].value) {
            stopPlay();
        }
    }
}

void Trigger::l_handlePress() {
    Modules::current = PLAY; 
    Display::newPage();
}

void Trigger::r_handlePress() {
}

