#ifndef MIDI_H
#define MIDI_H

void handleNoteOn(byte channel, byte pitch, byte velocity);
void handleNoteOff(byte channel, byte pitch, byte velocity);

#endif
