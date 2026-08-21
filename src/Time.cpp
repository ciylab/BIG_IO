/**
 * @file Time.cpp
 * @brief Gestion du temps.
 */
#include <MIDI.h> 
#include "Time.h"
#include "Modules.h"

using namespace MIDI_NAMESPACE;
extern MidiInterface<SerialMIDI<HardwareSerial>> MIDI; /**<interface MIDI*/

unsigned long Time::tick = 0;
unsigned long Time::delta = 2500000 / DEFAULT_BPM;
unsigned long Time::lastTime = micros();
unsigned long Time::lastClockIn = 0;
bool start = false;
bool Time::newTick = true;
/**
 * @brief Gestion de l'horloge.
 *
 * Commande de la led et des notes jouées par le métronome.
 */


void Time::handleClock() {
    if(this->io[0].value == 1) { // entrée midi
        MIDI.sendRealTime(midi::Clock);
        handleTick();
    }
}

void Time::handleStop() {
    if(this->io[0].value == 1) { // entrée midi
        MIDI.sendRealTime(midi::Stop);
    }
}


void Time::handleStart() {
    Time::tick = 0;
    if(this->io[0].value == 1) { // entrée midi
        MIDI.sendRealTime(midi::Start);
    }
}

void Time::handleTick() {
    Time::tick++;
    Time::newTick = true;
    if(this->io[3].value == 0) { // sortie clock activée
        turn_led();
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
    if(this->io[1].value == 2) {
        return;
    }
    byte modulo = 24 * (this->parameters[2].value + 3);
    byte channel = this->io[1].value - 2;
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

bool Time::play_rand() {
    return this->parameters[3].value <= random(6);
}

void Time::turn_led() {
    byte modulo = 24;
    byte ratio = this->parameters[1].value; // speed
    if(3 < ratio) {
        modulo = modulo / (ratio - 2);
    } else if (ratio < 3) {
        modulo = (4 - ratio) * modulo;
    }
    if (Time::tick % modulo == 0 && play_rand()) {
        digitalWrite(CLOCK_OUT, LOW);
    } else if (Time::tick % modulo == 2) {
        digitalWrite(CLOCK_OUT, HIGH);
    }
}

bool listen_clock_pulse() {
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

void Time::clock_send() {
    if(Time::delta < micros() - Time::lastTime) {
        MIDI.sendRealTime(midi::Clock);
        handleTick();
        Time::lastTime += Time::delta;
    }
}

void Time::execute() {
    Time::newTick = false;
    if(this->io[0].value == 2) { // entrée désactivée
        clock_send();
    } else if(this->io[0].value == 0) { // entrée trigger
        if(listen_clock_pulse()) {
            // Korg Electribe : SYNC UNIT 1 Step
            Time::delta = (micros() - Time::lastClockIn) / 6;
            Time::lastClockIn = micros();
        }
        if(Time::lastClockIn != 0 && 
                micros() - Time::lastClockIn < 1500000) {
            clock_send();
        }
    } else if(this->io[0].value == 1) { // entrée midi
        return;
    }
}

