/**
 * @file Trigger.cpp
 * @brief Gestion du temps.
 */
#include <MIDI.h>
#include "../time/Time.h"
#include "Trigger.h"
#include "../base/Modules.h"
#include "../base/encoder.h"

using namespace MIDI_NAMESPACE;
extern MidiInterface<SerialMIDI<HardwareSerial>> MIDI; /**<interface MIDI*/

bool Trigger::isPulse() {
    byte length = parameters[1].value;
    if ((parameters[2].value *
                (length - parameters[3].value + Time::tick / 6)) % length < 
            parameters[2].value) {
        return true;
    }
    // idem pour la deuxième séquence
    if ((parameters[6].value *
                (length - parameters[7].value + Time::tick / 6)) % length < 
            parameters[6].value) {
        return true;
    }
    return false;
}

void Trigger::startPulse() {
    if(1 <= parameters[0].value && parameters[0].value < 6) {
        digitalWrite(pins[parameters[0].value - 1], LOW);
    } else if(6 <= parameters[0].value && parameters[0].value < 22) {
        parameters[0].buffer = parameters[0].value;
        lastPitch = parameters[4].buffer;
        MIDI.sendNoteOn(lastPitch, 127, parameters[0].value - 5);
        Serial.println("note on");
    }
}

void Trigger::stopPulse() {
    if(1 <= parameters[0].value && parameters[0].value < 6) {
        digitalWrite(pins[parameters[0].value - 1], HIGH);
    } else if(6 <= parameters[0].value && parameters[0].value < 22) {
        MIDI.sendNoteOff(lastPitch, 0, parameters[0].buffer - 5);
        Serial.println("note off");
    }
}

void Trigger::execute() {
    if (
            parameters[0].value == 0 ||
            parameters[1].value == 0 || 
            parameters[2].value == 0) {
        return;
    }
    if(Time::newTick) {
        if(Time::tick % 6 == 0 && isPulse()) {
            startPulse();
            start = Time::tick;
        } else if (Time::tick == start + parameters[8].value) {
            stopPulse();
        }
    }
}

void Trigger::l_handlePress() {
    Modules::current = PLAY; 
    Display::newPage();
}

void Trigger::r_handlePress() {
    /*
    if(Display::cursor_num == 0) {
        hidden = !hidden;
        new_value = false;
        r_handleRotate(0);
    } else 
    */
    if(Display::cursor_num == 4) {
        parameters[4].buffer = parameters[4].value;
    }
}

