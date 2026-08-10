#include <MIDI.h>
#include <Versatile_RotaryEncoder.h>
#include <U8x8lib.h>
#include "src/base/encoder.h"
#include "src/base/Display.h"
#include "src/base/config.h"
#include "src/base/dac.h"
#include "src/base/eeprom.h"
#include "src/base/midi.h"
#include "src/base/Modules.h"
#include "src/base/Main.h"
#include "src/time/Time.h"
#include "src/base/Play.h"


Versatile_RotaryEncoder *left;
Versatile_RotaryEncoder *right;
MIDI_CREATE_DEFAULT_INSTANCE();

Display oled; /**<l'écran */
Modules *myModules = new Modules();

void setup() {
    Serial.begin(9600);
    pin_init();
    oled.begin();
    pin_test();
    myModules->add(new Main("MAIN"));
    myModules->add(new Time("TIME"));
    myModules->add(new Play("PLAY"));
    MIDI.begin(MIDI_CHANNEL_OMNI);
    MIDI.turnThruOff();
    MIDI.setHandleNoteOn(handleNoteOn);
    MIDI.setHandleNoteOff(handleNoteOff);
    MIDI.setHandleClock(handleClock);
    MIDI.setHandleStart(handleStart);
    MIDI.setHandleStop(handleStop);
    pinMode(PA0, INPUT_PULLUP);
    pinMode(PA1, INPUT_PULLUP);
    pinMode(PA2, INPUT_PULLUP);
    pinMode(PB0, INPUT_PULLUP);
    pinMode(PB1, INPUT_PULLUP);
    pinMode(PB10, INPUT_PULLUP);
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
    myModules->execute();
}
