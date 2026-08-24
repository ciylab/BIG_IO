#ifndef MIDI_H
#define MIDI_H
#include <Arduino.h>

void handleNoteOn(byte channel, byte pitch, byte velocity);
void handleNoteOff(byte channel, byte pitch, byte velocity);
void handleClock();
void handleStart();
void handleStop();
void handleTime();
void panic();
#endif
