#include <MIDI.h>
MIDI_CREATE_DEFAULT_INSTANCE();

void setup() {
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
    MIDI.begin(MIDI_CHANNEL_OMNI);
}

void loop() {
    if (MIDI.read()) {
        digitalWrite(LED_BUILTIN, HIGH);
        Serial.println("ON");
        delay(100);
        digitalWrite(LED_BUILTIN, LOW);
        Serial.println("OFF");
        delay(100);
    }
}

