/**
 * @file Random.cpp
 */

#include <MIDI.h>
#include "../Time.h"
#include "../Modules.h"
#include "../dac.h"
#include "Random.h"
#include "../encoder.h"

using namespace MIDI_NAMESPACE;
extern MidiInterface<SerialMIDI<HardwareSerial>> MIDI; /**<interface MIDI*/
/**
 * Nombre de notes dont la hauteur est inférieure
 * ou égale au rang.
 */
byte Random::count[NUM_SCALE][12] = {
    { 1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, },
    { 1,  1,  2,  2,  3,  4,  4,  5,  5,  6,  6,  7, },
    { 1,  1,  2,  2,  3,  3,  3,  4,  4,  5,  5,  5, },
    { 1,  1,  2,  3,  3,  4,  4,  5,  6,  6,  6,  7, },
};

/**
 * Tableaux de 0 et 1 suivant que la note est dans la gamme
 * ou pas.
 */
byte Random::scales[NUM_SCALE][12] = {
    { 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, },
    { 1,  0,  1,  0,  1,  1,  0,  1,  0,  1,  0,  1, },
    { 1,  0,  1,  0,  1,  0,  0,  1,  0,  1,  0,  0, },
    { 1,  0,  1,  1,  0,  1,  0,  1,  1,  0,  0,  1, },
};

/**
 * Rang des notes de la gamme.
 */
byte Random::pitchs[NUM_SCALE][12] = { // i-th pitch in C
    {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},  // chromatic
    {0, 2, 4, 5, 7, 9, 11},                  // major
    {0, 2, 4, 7, 9},                         // pentatonic
    {0, 2, 3, 5, 7, 8, 11},                  // harmonic
};

/**
 * @brief Retourne un nombre de notes.
 *
 * Pour une gamme donnée et une hauteur donnée, retourne
 * le nombre de notes inférieure ou égale à cette hauteur
 * dans cette gamme.
 */

byte Random::get_count(byte scale, byte note) {
    // lower pitch 
    int size = count[scale][11];
    return size * (note / 12) + 
        count[scale][note % 12] - scales[scale][note % 12];
}

/**
 * @brief Retourne une hauteur de note.
 *
 * Pour une gamme donnée et un rang donné, retourne
 * la hauteur correspondante.
 */
byte Random::get_pitch(byte scale, byte rank) {
    int size = count[scale][11];
    return 12 * (rank / size) + pitchs[scale][rank % size];
}

/**
 * @brief Retourne une hauteur de note aléatoire.
 *
 * Pour une gamme donnée et une tonalité donnée, retourne
 * une hauteur aléatoire comprise entre min (inclus) 
 * et max (exclus) pour un tirage uniforme.
 */
byte Random::rand_note(byte min, byte max, byte tone, byte scale) {
    int a = get_count(scale, min + 12 - tone);
    int b = get_count(scale, max + 12 - tone);
    // rank in the C range with uniform distribution
    int rank = random(a, b);
    // pitch in tone
    return tone + get_pitch(scale, rank) - 12;
}

/**
 * @brief Simple fonction retournant une note aléatoire dans le contexte.
 *
 */
byte Random::getRandomNote() {
    return rand_note(parameters[5].value, // min 
            parameters[6].value, // max 
            parameters[3].value, // tone
            parameters[2].value); // scale
}

bool Random::isInRange(byte pitch) {
    return parameters[5].value <= pitch && pitch < parameters[6].value;
}

void Random::l_handlePress() {
    Modules::current = PLAY; 
    Display::newPage();
}

void Random::startPlay() {
    current_index = Time::tick / 6 % this->parameters[0].value;
    if(this->parameters[4].value) { // frozen
        if(!isInRange(sequence[current_index])) {
            lastPitch = 255;
            return;
        }
    } else {
        sequence[current_index] = getRandomNote(); // new random note
    }
    lastPitch = sequence[current_index];
    if(2 < this->io[1].value) {
        this->io[1].buffer = this->io[1].value;
        MIDI.sendNoteOn(lastPitch, 127, this->io[1].value - 2);
    }
    if(1 < this->io[3].value) {
        this->io[3].buffer = this->io[3].value;
        digitalWrite(pins[this->io[3].value - 1], LOW);
    }
    if(this->io[2].value != 0) {        
        dac_write(this->io[2].value - 1, 
                Modules::getVoltage(lastPitch));
    }
}

void Random::stopPlay() {
    if(lastPitch == 255) {
        return;
    }
    if(2 < this->io[1].value) {
        MIDI.sendNoteOff(lastPitch, 0, this->io[1].buffer - 2);
    }
    if(1 < this->io[3].buffer) {
        digitalWrite(pins[this->io[3].buffer - 1], HIGH);
    }            
}

void Random::execute() {
    if(this->parameters[0].value == 0) {
        return;
    }
    if(this->parameters[6].value <= this->parameters[5].value ) {
        return;
    }
    if(Time::newTick) {
        if(Time::tick % 6 == 0) {
            startPlay();
            start = Time::tick;
        } else if (Time::tick == start + this->parameters[1].value) {
            stopPlay();
        }
    }
}

void Random::r_handlePress() {
}

void Random::panic() {
    if(2 < this->io[1].value) {
        for (byte pitch = 1; pitch <= 108; pitch++) {
            MIDI.sendNoteOff(pitch, 0, this->io[1].value - 2);
        }
        this->io[1].value = 2;
    }
}

