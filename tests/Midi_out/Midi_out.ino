#include <MIDI.h>
MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);
//MIDI_CREATE_DEFAULT_INSTANCE();

void setup() {
    MIDI.begin();
}

void loop() {
    MIDI.sendNoteOn(42, 127, 1);
    delay(500);
    MIDI.sendNoteOff(42, 0, 1);
    delay(500); 
}

