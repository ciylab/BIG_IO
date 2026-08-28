/**
 * @file Time.cpp
 */
#include <MIDI.h> 
#include "Time.h"
#include "Modules.h"

using namespace MIDI_NAMESPACE;
extern MidiInterface<SerialMIDI<HardwareSerial>> MIDI; /**<interface MIDI*/
unsigned long Time::tick;
bool Time::newTick;

void Time::init() {
    Time::tick = 0;
    Time::newTick = true;
    delta = 2500000 / DEFAULT_BPM;
    lastTime = micros();
    lastClockIn = 0;
    start = false;
}

void Time::handleClock() {
    if(this->io[0].value == 2) { // midi in
        MIDI.sendRealTime(midi::Clock);
        handleTick();
    }
}

void Time::handleStop() {
    if(this->io[0].value == 2) { // midi in
        MIDI.sendRealTime(midi::Stop);
    }
}


void Time::handleStart() {
    Time::tick = 0;
    if(this->io[0].value == 2) { // midi in
        MIDI.sendRealTime(midi::Start);
    }
}

void Time::handleTick() {
    Time::tick++;
    Time::newTick = true;
    if(this->io[3].value == 1) { // clock out
        handleGate();
    }
    Time::metronome();
}

void Time::l_handlePress() {
    Modules::current = PLAY;
    Display::newPage();
}

void Time::r_handlePress() {
}

void Time::metronome() {
    if(this->io[1].value == 0) {
        return;
    }
    byte modulo = 24 * (this->parameters[2].value + 3);
    byte channel = this->io[1].value;
    if(Time::tick % modulo == 0) {
        MIDI.sendNoteOn(48, 64, channel);
    } else if(Time::tick % modulo == 1) {
        MIDI.sendNoteOff(48, 0, channel);
    } else if(Time::tick % 24 == 0) {
        MIDI.sendNoteOn(24, 64, channel);
    } else if(Time::tick % 24 == 1) {
        MIDI.sendNoteOff(24, 0, channel);
    }
}

void Time::panic() {
    if(this->io[1].value != 0) {
        MIDI.sendNoteOff(48, 0, this->io[1].value);
        MIDI.sendNoteOff(24, 0, this->io[1].value);
    }
    this->io[1].value = 0;
}

bool Time::playRand() {
    return this->parameters[3].value <= random(6);
}

void Time::handleGate() {
    byte modulo = 24;
    byte ratio = this->parameters[1].value; // speed
    if(3 < ratio) {
        modulo = modulo / (ratio - 2);
    } else if (ratio < 3) {
        modulo = (4 - ratio) * modulo;
    }
    if (Time::tick % modulo == 0 && playRand()) {
        digitalWrite(CLOCK_OUT, LOW);
    } else if (Time::tick % modulo == 2) {
        digitalWrite(CLOCK_OUT, HIGH);
    }
}

bool Time::listen_clock_pulse() {
    int val = analogRead(CLOCK_IN);
    if(val < 500 && start == false) {
        start = true;
        return true;
    }
    if(val > 500 && start == true) {
        start = false;
    } 
    return false;
}

void Time::clockSend() {
    if(Time::delta < micros() - Time::lastTime) {
        MIDI.sendRealTime(midi::Clock);
        handleTick();
        Time::lastTime += Time::delta;
    }
}

void Time::execute() {
    Time::newTick = false;
    if(this->io[0].value == 0) { // no clock in
        clockSend();
    } else if(this->io[0].value == 1) { // clock in
        if(listen_clock_pulse()) {
            // Korg Electribe : SYNC UNIT 1 Step
            Time::delta = (micros() - Time::lastClockIn) / 6;
            Time::lastClockIn = micros();
        }
        if(Time::lastClockIn != 0 && 
                micros() - Time::lastClockIn < 1500000) {
            clockSend();
        }
    }
}

