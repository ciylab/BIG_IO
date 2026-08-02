#include <Versatile_RotaryEncoder.h>
#include <U8x8lib.h>
#include "src/base/encoder.h"
#include "src/base/Display.h"
#include "src/base/Pages.h"
#include "src/base/config.h"

Versatile_RotaryEncoder *left;
Versatile_RotaryEncoder *right;

Display oled; /**<l'écran */
Pages *ps = new Pages();

void setup() {
    Serial.begin(9600);
    init_data();
    oled.begin();
    oled.welcome();
	left = new Versatile_RotaryEncoder(PB0, PB1, PB10);
    left->setHandleRotate(l_handleRotate);
    left->setHandlePress(l_handlePress);
    left->setHandleLongPress(l_handleLongPress);
	right = new Versatile_RotaryEncoder(PA1, PA0, PA2);
    right->setHandleRotate(r_handleRotate);
    right->setHandlePress(r_handlePress);
    ps->init();
    //ps->test();
    delay(1000);
    oled.newPage(0);
}

void loop () {
    left->ReadEncoder();
    right->ReadEncoder();
    oled.display();
}
