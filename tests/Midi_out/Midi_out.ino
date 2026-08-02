#include <MIDI.h>
MIDI_CREATE_DEFAULT_INSTANCE();

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    MIDI.begin();
}

void loop() {
    digitalWrite(LED_BUILTIN, HIGH);
    MIDI.sendNoteOn(42, 127, 1);
    delay(500);
    MIDI.sendNoteOff(42, 0, 1);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500); 
}

