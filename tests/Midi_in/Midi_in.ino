#include <MIDI.h>
MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);
//MIDI_CREATE_DEFAULT_INSTANCE();

void setup() {
    Serial.begin(9600);
    MIDI.begin(MIDI_CHANNEL_OMNI);
}

void loop() {
    if (MIDI.read()) {
        Serial.println("OK");
        delay(100);
    }
}

