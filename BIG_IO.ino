#include <MIDI.h>
#include <Versatile_RotaryEncoder.h>
#include <U8x8lib.h>
#include "src/encoder.h"
#include "src/Display.h"
#include "src/gate.h"
#include "src/dac.h"
#include "src/eeprom.h"
#include "src/midi.h"
#include "src/Modules.h"

/**
 * Turn to change cursor position and press to go back in menus.
 */
Versatile_RotaryEncoder *left;
/**
 * Turn to change value and press to vamidate some choice.
 */
Versatile_RotaryEncoder *right;
/**
 * Display with empty text.
 */
Display oled;
/**
 * A shell for the modules.
 * - Main page
 * - Conf page
 * - io page
 * - Play page
 */
Modules *myModules = new Modules();

MIDI_CREATE_DEFAULT_INSTANCE();

void setup() {
    Serial.begin(9600);
    pin_init();   // init all pins
    gates_test();  // lights
    oled.begin(); // font and welcome page
    /*
     * Midi part.
     */
    MIDI.begin(MIDI_CHANNEL_OMNI);
    MIDI.turnThruOff();
    MIDI.setHandleNoteOn(handleNoteOn);
    MIDI.setHandleNoteOff(handleNoteOff);
    MIDI.setHandleClock(handleClock);
    MIDI.setHandleStart(handleStart);
    MIDI.setHandleStop(handleStop);
    /*
     * left encoder
     */
    left = new Versatile_RotaryEncoder(PB0, PB1, PB10);
    left->setHandleRotate(l_handleRotate);
    left->setHandlePress(l_handlePress);
    left->setHandleLongPress(l_handleLongPress);
    /*
     * right encoder
     */
    right = new Versatile_RotaryEncoder(PA1, PA0, PA2);
    right->setHandleRotate(r_handleRotate);
    right->setHandlePress(r_handlePress);
    /*
     * load data from eeprom
     */
    init_from_eeprom();
    /*
     * SPI dac
     */
    init_dac();
    delay(1000);    // to have time to read the welcome page
    oled.newPage(); //
}

/**
 * Main loop :
 *
 * 1. read midi
 * 2. read encoders
 * 3. write display
 * 4. execute each module
 */
void loop () {
    MIDI.read();
    left->ReadEncoder();
    right->ReadEncoder();
    oled.display();
    myModules->execute();
}
