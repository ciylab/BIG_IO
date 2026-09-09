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
 * @brief Change value of paramters
 *
 * @param channel of the module we want to change values
 * @param number CC from 1 to size 
 * @param value the new value from 0 to 127 mapped
 * */
void handleControlChange(byte channel, byte number, byte value);
/**
 * @brief Go to module page from PLAY
 *
 * @param channel unused
 * @param number the module num from 0 to 7 (example 0 for TIME)
 */
void handleProgramChange(byte channel, byte number);
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

