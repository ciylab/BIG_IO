/**
 * @file dac.cpp
 */
#include "dac.h"
#include <SPI.h>

void init_dac() {
    pinMode(CS1, OUTPUT);
    pinMode(CS2, OUTPUT);
    digitalWrite(CS1, HIGH);
    digitalWrite(CS2, HIGH);    
    SPI.begin();
}

void dac_write(byte ch, int cv) {
    if (ch == 0) {
        digitalWrite(CS1, LOW);
        SPI.transfer((cv >> 8) | 0x30);  // H0x30=OUTA/1x
        SPI.transfer(cv & 0xff);
        digitalWrite(CS1, HIGH);
    } else if(ch == 1) {
        digitalWrite(CS1, LOW);
        SPI.transfer((cv >> 8) | 0xB0);  // H0xB0=OUTB/1x
        SPI.transfer(cv & 0xff);
        digitalWrite(CS1, HIGH);
    } else if(ch == 2) { // MCP4921
        digitalWrite(CS2, LOW);
        SPI.transfer((cv >> 8) | 0x30);  // H0x30=OUTA/1x
        SPI.transfer(cv & 0xff);
        digitalWrite(CS2, HIGH);    
    }
}

unsigned int calibrate(byte val) {
    unsigned int cv = 3276 - 128 + val;
    dac_write(0, cv);
    dac_write(1, cv / 2);
    dac_write(2, cv / 4);
    return cv;
}
