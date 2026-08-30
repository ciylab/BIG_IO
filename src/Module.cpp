/**
 * @file Module.cpp
  */
#include <MIDI.h>
#include "Module.h"
#include "dac.h"

using namespace MIDI_NAMESPACE;
extern MidiInterface<SerialMIDI<HardwareSerial>> MIDI; /**<interface MIDI*/

/**
 * @brief Names of the module by type.
 *
 * Used to show on pages PLAY and CONF. 
 * It is better to store the names in array than to extract from class
 * for direct access.
 *
 * @see Conf.h
 * @see Play.h
 */
char *names[7] = {
    "TIME  ", 
    "BASS  ", 
    "RANDOM", 
    "REDIR ", 
    "DRUM  ", 
    "SEQ   ", 
    "NONE"
};

Module::Module() {
    size = 0;
    indexInList = 6;
    new_value = false;
    for (int i = 0; i < 64; i++) {
        text[i] = ' ';
    }
}

void Module::add(parameter p) {
    parameters[size] = p;
    size++;
}

void Module::setMenu() {
    byte offset;
    for (int i = 0; i < size; i++) {
        offset = parameters[i].cursor_pos;
        for (int j = 0; j < 7; j++) {
            text[j + offset] = parameters[i].name[j];
        }
    }
}

void Module::startPlayMIDI(byte pitch){
    this->io[1].buffer = this->io[1].value;
    if(this->io[1].value != 0) {
        MIDI.sendNoteOn(pitch, 127, this->io[1].value);
    }
}

void Module::startPlayCV(byte pitch) {
    if(this->io[2].value != 0) {        
        dac_write(this->io[2].value - 1, getVoltage(pitch));
    }
}

void Module::startPlayGate() {
    this->io[3].buffer = this->io[3].value;
    if(this->io[3].value != 0) {
        digitalWrite(gates[this->io[3].value - 1], LOW);
    }
}

void Module::stopPlayMIDI(byte pitch) {
    if(this->io[1].buffer != 0) {
        MIDI.sendNoteOff(pitch, 0, this->io[1].buffer);
    }
}

void Module::stopPlayCV(byte pitch) {
    if(this->io[2].value != 0) {        
        dac_write(this->io[2].value - 1, 0);
    }
}

void Module::stopPlayGate() {
    if(this->io[3].buffer != 0) {
        digitalWrite(gates[this->io[3].buffer - 1], HIGH);
    }
}

void Module::l_handlePress() {
}

void Module::r_handlePress() {
}


