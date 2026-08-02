#include <U8x8lib.h>

U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(U8X8_PIN_NONE);

void setup(void) {
    u8x8.begin();
    u8x8.setFont(u8x8_font_7x14_1x2_r);
    u8x8.drawString(0,0,"Hello HEX!");
}

void loop(void) {
}
