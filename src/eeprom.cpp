/**
 * @file eeprom.cpp
 * @brief Définition des fonctions de gestion de la mémoire.
 *
 * Il faut attendre 5 millisecondes par transmission pour écriture.
 */
#include <Wire.h>
#include "eeprom.h"
#include "Modules.h"

#define eeprom 0x50
#define CONFIG_SIZE 24

extern Modules *myModules;

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
//write_factory();
//write_simple();

/*
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
        writeEEPROM(eeprom, offset + 3 * i + 2, 
            myModules->modules[i + 2]->indexInList);
    }
}

/**
 * @brief Cette fonction remplace la configuration courante par
 * des données en eeprom.
 *
 * Le paramètre est le rang dans la mémoire. Il est indépendant de l'ID.
 */

void load(int slot_num) {
    byte action;
    int offsetInMemory = slot_num * CONFIG_SIZE;
    byte offsetInPlayPage;
    for(int i = 0; i < 8; i++) {
        action = readEEPROM(eeprom, offsetInMemory + 3 * i + 2);
        myModules->modules[i + 2] = Modules::getModule(action);
        myModules->modules[i + 2]->indexInList = action;
        myModules->modules[PLAY]->parameters[i].value = action;
        myModules->modules[PLAY]->parameters[i].buffer = action;
        offsetInPlayPage = 
            myModules->modules[PLAY]->parameters[i].cursor_pos;
        for (int j = 0; j < 4; j++) {
            myModules->modules[PLAY]->text[j + offsetInPlayPage + 3] = 
                myModules->modules[i + 2]->name[j];
        }

    }
}

/**
 * @brief Write default values (factory preset) in the first slot.
 */

void write_factory() {
    algo t[8] = {
        {0, 0, 1}, // TIME
        {0, 0, 4}, // SIMPLE
        {0, 0, 5}, // TRIG
        {0, 0, 2}, // MINISQ
        {0, 0, 6}, // RECORD
        {0, 0, 3}, // RAND
        {0, 0, 0}, // NONE
        {0, 0, 5}  // TRIG
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
        {0, 0, 1}, // clock
        {0, 0, 4}, // canal 1 -> CV/GATE
        {0, 0, 4}, // canal 2 -> CV/GATE
        {0, 0, 4}, // canal 3 -> CV/GATE 
        {0, 0, 4},  // changement de canal MIDI 4 -> 5
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
