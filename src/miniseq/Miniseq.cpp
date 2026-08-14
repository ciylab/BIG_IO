/**
 * @file Miniseq.cpp
 */

#include <MIDI.h>
#include "../time/Time.h"
#include "../base/Modules.h"
#include "../base/dac.h"
#include "../base/encoder.h"
#include "Miniseq.h"

using namespace MIDI_NAMESPACE;
extern MidiInterface<SerialMIDI<HardwareSerial>> MIDI; /**<interface MIDI*/

void Miniseq::startPlay() {
    lastPitch = this->parameters[3 + noteIndex].value - 1;
    if(this->parameters[0].value != 0) {
        // pour prévenir l'absence de note off
        this->parameters[0].buffer = this->parameters[0].value;
        MIDI.sendNoteOn(lastPitch,
                127, this->parameters[0].buffer);
    }
    if(this->parameters[1].value != 0) {
        this->parameters[1].buffer = this->parameters[1].value;
        digitalWrite(pins[parameters[1].value], LOW);
    }
    if(this->parameters[2].value != 0) {        
        dac_write(this->parameters[2].value - 1, 
                Modules::getVoltage(lastPitch));
    }
}

void Miniseq::stopPlay() {
    if(this->parameters[0].buffer != 0) {
        this->parameters[0].buffer = this->parameters[0].value;
        MIDI.sendNoteOff(lastPitch,
                0, this->parameters[0].buffer);
    }
    if(this->parameters[1].buffer != 0) {
        digitalWrite(pins[parameters[1].buffer], HIGH);
    }            
    noteIndex = (noteIndex + 1) % 5; 
    if(this->parameters[3 + noteIndex].value == 0) {
        noteIndex = 0; // la note est NONE et la boucle est finie
    }
}

void Miniseq::execute() {
    if(this->parameters[3].value == 0) {
        return ;
    }
    if(Time::newTick) {
        if(Time::tick % 6 == 0) {
            startPlay();
            start = Time::tick;
        } else if (Time::tick == start + this->parameters[8].value) {
            stopPlay();
        }
    }
}

void Miniseq::l_handlePress() {
    Modules::current = PLAY; 
    Display::newPage();
}

void Miniseq::r_handlePress() {
    if(Display::cursor_num == 1) {
        hidden = !hidden;
        new_value = false;
        r_handleRotate(0);
    } else if(2 < Display::cursor_num) {
        parameter *p;
        p = &parameters[Display::cursor_num];
        if (p->value != 0) {
            p->buffer = p->value;
            p->value = 0;
            MIDI.sendNoteOff(lastPitch,
                    0, this->parameters[0].buffer);
            digitalWrite(pins[parameters[1].value - 1], HIGH);
        } else {
            p->value = p->buffer;
        }
        Display::show_value(p->value);
    }
}
