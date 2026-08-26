/**
 * @file Display.cpp
 */

#include <U8x8lib.h>
#include "Display.h"
#include "config.h"
#include "Modules.h"
#include "my_u8x8_font_7x14_1x2_r.h"

extern Modules *myModules;

U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(U8X8_PIN_NONE);

char Display::screen[TEXT_SIZE];
char Display::buffer[TEXT_SIZE];
byte Display::charIndex = 0;
byte Display::endPosition = 63;
byte Display::cursor_num = 0;
byte Display::cursor_pos = 0;

int count = 0;

char *in[18] = {
    "NONE ", // 0
    "CH1  ", "CH2  ", "CH3  ", "CH4  ", // 1
    "CH5  ", "CH6  ", "CH7  ", "CH8  ", // 5
    "CH9  ", "CH10 ", "CH11 ", "CH12 ", // 9
    "CH13 ", "CH14 ", "CH15 ", "CH16 ", // 13
    "TRIG0"  // 17
};   

char *out[28] = {
    "NONE ", // 0
    "CH1  ", "CH2  ", "CH3  ", "CH4  ", // 1
    "CH5  ", "CH6  ", "CH7  ", "CH8  ", // 5
    "CH9  ", "CH10 ", "CH11 ", "CH12 ", // 9 
    "CH13 ", "CH14 ", "CH15 ", "CH16 ", // 13
    "TRIG1", "TRIG2", "TRIG3", "TRIG4", "TRIG5", // 17
    "CV1  ", "CV2  ", "CV3  ", // 22
    "CVGT1", "CVGT2", "CVGT3"  // 25
};

Display::Display() {
    for (int i = 0; i < TEXT_SIZE; i++) {
        screen[i] = ' ';
    }
    screen[63] = '\0';
}

void Display::begin() {
    u8x8.begin();
    u8x8.setFont(my_u8x8_font_7x14_1x2_r);
    welcome();
}
    
void Display::putChar(byte position, char c) {
    u8x8.drawGlyph(position % 16, 2 * (position / 16), c);
}

void Display::welcome() {
    sprintf(screen, "  BIG InOut       MIDI/CV/GATE    BY CIYLAB       %s",
            VERSION);
    for (int i = 0; i < 63; i++) {
        putChar(i, screen[i]);
    }
}

void Display::display() {
    // without buffer : 100ms
    // with buffer : 2ms
    if (endPosition <= charIndex) {
        return;
    }
    while (charIndex < endPosition && 
        screen[charIndex] == buffer[charIndex]) {
        charIndex++;
    }
    putChar(charIndex, buffer[charIndex]);
    screen[charIndex] = buffer[charIndex];
    charIndex++;
}

void Display::newPage() {
    sprintf(buffer, myModules->modules[Modules::current]->text);
#ifdef DEBUG
    for(int i = 0; i < TEXT_SIZE; i++) {
        Serial.print(buffer[i]);
    }
    Serial.println();
#endif
    charIndex = 0;
    endPosition = 63;
    putChar(cursor_pos, ' ');
    cursor_num = 0;
    cursor_pos = 0;
    putChar(cursor_pos, '>');
}

void Display::show_value(int val) {
    if(Modules::current == MAIN && (cursor_num == 0 || cursor_num == 2)) {
        return;
    }
    char temp[8];
    myModules->modules[Modules::current]->getString(val, temp);
    print_here(temp);
}

void Display::no_show_value(parameter p) {
    if(Modules::current == PLAY) {
        return;
    }
    print_here(p.name);
}

void Display::print_here(char *word) {
    charIndex = cursor_pos;
    endPosition = charIndex + 7;
    for (int i = 0; i < 7 && word[i] != '\0'; i++) {
        buffer[charIndex + i] = word[i];
    }
}
