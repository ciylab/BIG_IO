/**
 * @file dac.cpp
 * @brief Définition de la fonction qui envoie l'information vers 
 * le DAC.
 */
#include "dac.h"
#include <SPI.h>

#define CS1 PA4
#define CS2 PC15

/**
    Build the 16-bit command word:
    Bit 15: A/B (0 for MCP4921)
    Bit 14: Buffered VREF (0 = unbuffered, 1 = buffered)
    Bit 13: Output Gain (1 = 1x, 0 = 2x)
    Bit 12: Shutdown control (1 = active operation)
    Bits 11-0: 12-bit data value
*/

/**
 * @brief Cette fonction d'encapsulation initialise les dacs.
 */
void init_dac() {
    pinMode(CS1, OUTPUT);
    pinMode(CS2, OUTPUT);
    digitalWrite(CS1, HIGH);
    digitalWrite(CS2, HIGH);    
    SPI.begin();
}

/**
 * @brief Cette fonction envoie un entier **cv** compris entre 0 et 4095
 * sur un des deux canaux du dac 12-bit.
 */
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

/**
 * @brief Cette fonction permet de calibrer les CVs.
 *
 * La fonction permet d'envoyer exactement 4 volts pour C4 sur CV1.
 * On doit observer 2 volts sur CV2 et 1 volt sur CV3. La valeur est
 * conservée en mémoire dans les paramètres et sert de valeur de 
 * référence dans les actions.
 */
void calibrate(byte val) {
    int cv = (int) val - 128;
    dac_write(0, 3276 + cv);
    dac_write(1, 1638 + cv / 2);
    dac_write(2, 819 + cv / 4);
}
