#include <MIDI.h>
#include <Versatile_RotaryEncoder.h>
#include <U8x8lib.h>
#include "src/base/encoder.h"
#include "src/base/Display.h"
#include "src/base/config.h"
#include "src/base/dac.h"
#include "src/base/eeprom.h"
#include "src/base/midi.h"
#include "src/base/Module.h"

Versatile_RotaryEncoder *left;
Versatile_RotaryEncoder *right;
MIDI_CREATE_DEFAULT_INSTANCE();

Display oled; /**<l'écran */

void setup() {
    Serial.begin(9600);
    init_modules();
    oled.begin();
    MIDI.begin(MIDI_CHANNEL_OMNI);
    MIDI.turnThruOff();
    MIDI.setHandleNoteOn(handleNoteOn);
    MIDI.setHandleNoteOff(handleNoteOff);
    left = new Versatile_RotaryEncoder(PB0, PB1, PB10);
    left->setHandleRotate(l_handleRotate);
    left->setHandlePress(l_handlePress);
    left->setHandleLongPress(l_handleLongPress);
    right = new Versatile_RotaryEncoder(PA1, PA0, PA2);
    right->setHandleRotate(r_handleRotate);
    right->setHandlePress(r_handlePress);
    init_from_eeprom();
    init_dac();
    delay(1000);
    oled.newPage();
}

void loop () {
    MIDI.read();
    left->ReadEncoder();
    right->ReadEncoder();
    oled.display();
}
