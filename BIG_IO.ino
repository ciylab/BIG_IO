#include <Versatile_RotaryEncoder.h>
#include <U8x8lib.h>
#include "src/base/encoder.h"
#include "src/base/Display.h"
#include "src/base/Pages.h"
#include "src/base/config.h"
#include "src/base/dac.h"
#include "src/base/eeprom.h"

Versatile_RotaryEncoder *left;
Versatile_RotaryEncoder *right;

Display oled; /**<l'écran */
Pages *ps = new Pages();

void setup() {
    Serial.begin(9600);
    oled.begin();
    oled.welcome();
    left = new Versatile_RotaryEncoder(PB0, PB1, PB10);
    left->setHandleRotate(l_handleRotate);
    left->setHandlePress(l_handlePress);
    left->setHandleLongPress(l_handleLongPress);
    right = new Versatile_RotaryEncoder(PA1, PA0, PA2);
    right->setHandleRotate(r_handleRotate);
    right->setHandlePress(r_handlePress);
    init_dac();
    ps->init();
    //ps->test();
    init_data();
    init_from_eeprom();
    delay(1000);
    oled.newPage(0);
}

void loop () {
    left->ReadEncoder();
    right->ReadEncoder();
    oled.display();
}
