/**
 * @file midid.h
 * Each module can have own functions for handle midi input.
 */
#ifndef MIDI_H
#define MIDI_H
#include <Arduino.h>

void handleNoteOn(byte channel, byte pitch, byte velocity);
void handleNoteOff(byte channel, byte pitch, byte velocity);
void handleClock();
void handleStart();
void handleStop();
/**
 * @brief Send all note off for all the modules.
 */
void panic();
/**
 * @brief Send all note off
 *
 * @param channel the output channel
 */
void clear_channel(byte channel);
#endif
