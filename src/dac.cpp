/**
 * @file dac.cpp
 */
#include "dac.h"
#include <SPI.h>

/**
 * The cv value send to the dac for 4 volts.
 */
unsigned int C4RefVolt;

void init_dac() {
    pinMode(CS1, OUTPUT);
    pinMode(CS2, OUTPUT);
    digitalWrite(CS1, HIGH);
#ifdef nanor4
    analogWriteResolution(12);   
#elif bluepill
    digitalWrite(CS2, HIGH);    
#endif
    SPI.begin();
    C4RefVolt = 3277;
}

void dac_write(byte ch, int cv) {
    if (cv < 0) {
        cv = 0;
    } else if(4095 < cv) {
        cv = 4095;
    }
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
#ifdef bluebill
        digitalWrite(CS2, LOW);
        SPI.transfer((cv >> 8) | 0x30);  // H0x30=OUTA/1x
        SPI.transfer(cv & 0xff);
        digitalWrite(CS2, HIGH);    
#elif nanor4
        analogWrite(CS2, cv);
#endif    
    }
}

void calibrate(int8_t rotation) {
    if(rotation < 0) {
        C4RefVolt--;
    } else if(0 < rotation) {
        C4RefVolt++;
    }
    dac_write(0, C4RefVolt);
}

int getVoltage(byte pitch) {
    return (int) round(1. * pitch * C4RefVolt / 48);
}

