/**
 * @file Random.cpp
 */

#include <MIDI.h>
#include "../time/Time.h"
#include "../base/Modules.h"
#include "../base/dac.h"
#include "Random.h"
#include "../base/encoder.h"

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
    return rand_note(min, max, parameters[5].value, parameters[4].value);
}

bool Random::isInRange(byte pitch) {
    return min <= pitch && pitch < max;
}

void Random::l_handlePress() {
    Modules::current = PLAY; 
    Display::newPage();
}

void Random::startPlay() {
    current_index = Time::tick / 6 % this->parameters[3].value;
    if(this->parameters[6].value) { // frozen
        if(!isInRange(sequence[current_index])) {
            lastPitch = 255;
            return;
        }
    } else {
        sequence[current_index] = getRandomNote(); // new random note
    }
    lastPitch = sequence[current_index];
    this->parameters[0].buffer = this->parameters[0].value;
    this->parameters[1].buffer = this->parameters[1].value;
    if(this->parameters[0].value != 0) {
        MIDI.sendNoteOn(lastPitch,
                127, this->parameters[0].value);
    }
    if(this->parameters[1].value != 0) {
        digitalWrite(pins[parameters[1].value], LOW);
    }
    if(this->parameters[2].value != 0) {        
        dac_write(this->parameters[2].value - 1, 
                Modules::getVoltage(lastPitch));
    }
}

void Random::stopPlay() {
    if(lastPitch == 255) {
        return;
    }
    if(this->parameters[0].buffer != 0) {
        MIDI.sendNoteOff(lastPitch, 0, this->parameters[0].buffer);
    }
    if(this->parameters[1].buffer != 0) {
        digitalWrite(pins[parameters[1].buffer], HIGH);
    }            
}

void Random::execute() {
    if(this->parameters[3].value == 0) {
        return;
    }
    if(max <= min) {
        return;
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

void Random::r_handlePress() {
    if(Display::cursor_num == 1) {
        hidden = !hidden;
        new_value = false;
        r_handleRotate(0);
    } else if(Display::cursor_num == 7) {
        hidden = true;
        if(showMax) {
            this->parameters[7].value = max;
        } else {
            this->parameters[7].value = min + 108;
        }
        showMax = !showMax;
        new_value = false;
        r_handleRotate(0);
    }
}

