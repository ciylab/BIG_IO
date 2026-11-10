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
#ifdef nanor4
    pinMode(CS1, OUTPUT);
    analogWriteResolution(12);   
#elif bluepill
    pinMode(CS1, OUTPUT);
    pinMode(CS2, OUTPUT);
    digitalWrite(CS2, HIGH);    
#endif
    digitalWrite(CS1, HIGH);
    SPI.begin();


#ifdef bluepill
    //SPI.beginTransaction(SPISettings(2000000, MSBFIRST, SPI_MODE0));
#endif
    C4RefVolt = 3277;
}

void writeMCP4921(uint8_t CS, uint16_t value) {
    SPI.beginTransaction(SPISettings(20000000, MSBFIRST, SPI_MODE0));
    value &= 0x0FFF; 
    uint16_t commande = 0x3000 | value;
    digitalWrite(CS, LOW);
    SPI.transfer16(commande);
    digitalWrite(CS, HIGH);
    SPI.endTransaction();
}

void writeMCP4922(uint8_t CS, uint8_t ch, uint16_t value) {
    value &= 0x0FFF; 
    uint16_t commande = 0x3000 | value; 
    if (ch == 1) {
        commande |= 0x8000;
    }
    SPI.beginTransaction(SPISettings(20000000, MSBFIRST, SPI_MODE0));
    digitalWrite(CS, LOW);
    SPI.transfer16(commande);
    digitalWrite(CS, HIGH);
    SPI.endTransaction();
}

void dac_write(uint8_t ch, uint16_t value) {
#ifdef nanor4
    switch(ch) {
        case 0:
            digitalWrite(CS1, LOW);
            SPI.transfer((value >> 8) | 0x30);  // H0x30=OUTA/1x
            SPI.transfer(value & 0xff);
            digitalWrite(CS1, HIGH);
            break;
        case 1:
            digitalWrite(CS1, LOW);
            SPI.transfer((value >> 8) | 0xB0);  // H0xB0=OUTB/1x
            SPI.transfer(value & 0xff);
            digitalWrite(CS1, HIGH);
            break;
        case 2:
            analogWrite(DAC, value);
            break;
    } 
#elif bluepill
    switch(ch) {
        case 0:
            writeMCP4921(CS1, value);
            break;
        case 1:
            writeMCP4922(CS2, 1, value);
            break;
        case 2:
            writeMCP4922(CS2, 0, value);
            break;
    }
#endif    
}    

void calibrate(int8_t rotation) {
    if(rotation < 0) {
        C4RefVolt--;
    } else if(0 < rotation) {
        C4RefVolt++;
    }
    dac_write(0, C4RefVolt);
    dac_write(1, C4RefVolt);
    dac_write(2, C4RefVolt);
}

int getVoltage(int8_t pitch) {
    int val = (int) round(1. * pitch * C4RefVolt / 48);
    if (4095 < val) {
        return 4095;
    }
    return val;
}

