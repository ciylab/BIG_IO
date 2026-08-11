/**
 * @file eeprom.cpp
 * @brief Définition des fonctions de gestion de la mémoire.
 *
 * Il faut attendre 5 millisecondes par transmission pour écriture.
 */
#include <Wire.h>
#include "eeprom.h"
#include "config.h"

#define eeprom 0x50
#define CONFIG_SIZE 24

extern algo algos[8];

void writeEEPROM(int deviceaddress, unsigned int eeaddress, byte data ) {
    Wire.beginTransmission(deviceaddress);
    Wire.write((int)(eeaddress >> 8));      //writes the MSB
    Wire.write((int)(eeaddress & 0xFF));    //writes the LSB
    Wire.write(data);
    Wire.endTransmission();
    delay(5); // important!
}

byte readEEPROM(int deviceaddress, unsigned int eeaddress ) {
    byte rdata = 0xFF;
    Wire.beginTransmission(deviceaddress);
    Wire.write((int)(eeaddress >> 8));      //writes the MSB
    Wire.write((int)(eeaddress & 0xFF));    //writes the LSB
    Wire.endTransmission();
    Wire.requestFrom(deviceaddress,1);
    if (Wire.available()) { 
        rdata = Wire.read();
    }
    return rdata;
}

/**
 * @brief Fonction d'initialisation.
 */

void init_from_eeprom() {
    Wire.begin();
    /**
     * code pour initialiser l'EEPROM :
     */
/*
    write_factory();
    write_simple();
    for(int i = 2; i < 8; i++) {
        write_null(i);
    }
    */
    load(0); // load from factory preset FACT.
}

/**
 * @brief Cette fonction enregistre en eeprom la configuration
 * courante.
 *
 * Le paramètre est le rang dans la mémoire. Il est indépendant de l'ID.
 */

void save(int slot_num) {
    if(slot_num == 0) {
        return;
    }
    int offset = slot_num * CONFIG_SIZE;
    for(int i = 0; i < 8; i++) {
        writeEEPROM(eeprom, offset + 3 * i, algos[i].in);
        writeEEPROM(eeprom, offset + 3 * i + 1, algos[i].out);
        writeEEPROM(eeprom, offset + 3 * i + 2, algos[i].action);
    }
}

/**
 * @brief Cette fonction remplace la configuration courante par
 * des données en eeprom.
 *
 * Le paramètre est le rang dans la mémoire. Il est indépendant de l'ID.
 */

void load(int slot_num) {
    int offset = slot_num * CONFIG_SIZE;
    for(int i = 0; i < 8; i++) {
        algos[i].in = readEEPROM(eeprom, offset + 3 * i);
        algos[i].out = readEEPROM(eeprom, offset + 3 * i + 1);
        algos[i].action = readEEPROM(eeprom, offset + 3 * i + 2);
    }
    load_modules();
}

/**
 * @brief Write default values (factory preset) in the first slot.
 */

void write_factory() {
    algo t[8] = {
        {17, 17, 6}, // SIMPLE
        {0, 18, 7},  // TRIG
        {0, 19, 7},  // TRIG
        {0, 1, 3},   // MINISQ
        {2, 2, 5},   // RECORD
        {0, 25, 4},  // RAND
        {3, 3, 0},   // NONE
        {14, 26, 6}  // SIMPLE
    };
    for(int i = 0; i < 8; i++) {
        writeEEPROM(eeprom, 3 * i, t[i].in);
        writeEEPROM(eeprom, 3 * i + 1, t[i].out);
        writeEEPROM(eeprom, 3 * i + 2, t[i].action);
    }
}

/**
 * @brief Write simple the second slot.
 */

void write_simple() {
    algo t[8] = {
        {0, 17, 6}, // clock
        {1, 25, 6}, // canal 1 -> CV/GATE
        {2, 26, 6}, // canal 2 -> CV/GATE
        {3, 27, 6}, // canal 3 -> CV/GATE 
        {4, 5, 6},  // changement de canal MIDI 4 -> 5
        {0, 0, 0}, 
        {0, 0, 0}, 
        {0, 0, 0} 
    };
    for(int i = 0; i < 8; i++) {
        writeEEPROM(eeprom, CONFIG_SIZE + 3 * i, t[i].in);
        writeEEPROM(eeprom, CONFIG_SIZE + 3 * i + 1, t[i].out);
        writeEEPROM(eeprom, CONFIG_SIZE + 3 * i + 2, t[i].action);
    }
}

/**
 * @brief Write null values (factory preset) in the other slot.
 */

void write_null(int id) {
    unsigned int offset = id * CONFIG_SIZE;
    for(int i = 0; i < CONFIG_SIZE; i++) {
        writeEEPROM(eeprom, offset + i, 0);
    }
}
