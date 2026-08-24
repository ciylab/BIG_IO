/**
 * @file eeprom.cpp
 * @brief Définition des fonctions de gestion de la mémoire.
 *
 * Il faut attendre 5 millisecondes par transmission pour écriture.
 */
#include <Wire.h>
#include "eeprom.h"
#include "Modules.h"
#include "midi.h"

#define eeprom 0x50
/** 
 * @brief La taille en byte du nombre de paramètres à sauvegarder 
 * par module.
 *
 * - l'index pour caractériser le type de module
 * - les 4 paramètres IN/OUT
 * - les 8 paramètres 
 */
#define CONFIG_SIZE 13

extern Modules *myModules;
extern char *names[];

bool other_config = false;

void writeEEPROM(int deviceaddress, unsigned int eeaddress, byte data) {
    Wire.beginTransmission(deviceaddress);
    Wire.write((int)(eeaddress >> 8));      //writes the MSB
    Wire.write((int)(eeaddress & 0xFF));    //writes the LSB
    Wire.write(data);
    Wire.endTransmission();
    delay(5); // important!
}

byte readEEPROM(int deviceaddress, unsigned int eeaddress) {
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

void updateEEPROM(int deviceaddress, unsigned int eeaddress, byte data) {
    byte temp;
    temp = readEEPROM(deviceaddress, eeaddress);
    if (temp != data) {
        writeEEPROM(deviceaddress, eeaddress, data);
    }
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
 * @param slot_num le rang dans la mémoire.
 */

void save(int slot_num) {
    if(slot_num == 0) {
        return;
    }
    // Le byte à partir duquel on écrit.
    int offset = 8 * slot_num * CONFIG_SIZE;
    for(int i = 0; i < 8; i++) {
        save_module(offset + i * CONFIG_SIZE, i);
    }
}

/**
 * @brief Cette fonction enregistre le i-ième module courant
 * à partir de l'offset du slot.
 *
 * @param offset numéro du premier byte
 * @param module_num numéro du module de 0 à 7
 */
void save_module(int offset, byte module_num) {
    Module *m = myModules->modules[TIME + module_num];
    byte temp;
    writeEEPROM(eeprom, offset++, m->indexInList);
    for(int i = 0; i < 4; i++) {
        updateEEPROM(eeprom, offset++, m->io[i].value);
    }
    for(int i = 0; i < m->size; i++) {
        updateEEPROM(eeprom, offset++, m->parameters[i].value);
    }
    for(int i = m->size; i < 8; i++) {
        updateEEPROM(eeprom, offset++, 0);
    }
    serial_data(module_num);
}

/**
 * @brief Pour libérer la mémoire.
 */

void free_memory() {
    // very important !!!!
    if(other_config) {
        for (byte module_num = 0; module_num < 8; module_num++) {
            delete myModules->modules[TIME + module_num];
            myModules->modules[TIME + module_num] = NULL;
        }
    }
    other_config = true;
}

/**
 * @brief Cette fonction remplace la configuration courante par
 * des données en eeprom.
 *
 * @param slot_num le rang dans la mémoire.
 */

void load(int slot_num) {    
    // Le byte à partir duquel on écrit.
    int offset = 8 * slot_num * CONFIG_SIZE;
    free_memory();
    for(int i = 0; i < 8; i++) {
        load_module(offset + i * CONFIG_SIZE, i);
    }
    // On envoie plus rien sur les gates
    pin_init();
    // MIDI panic !!!
    panic();
}

/**
 * @brief Cette fonction charge le i-ième module courant
 * à partir de l'offset du slot.
 *
 * @param offset numéro du premier byte
 * @param module_num numéro du module de 0 à 7
 */
void load_module(int offset, byte module_num) {
    byte index = readEEPROM(eeprom, offset++);
    myModules->modules[TIME + module_num] = Modules::getModule(index);
    myModules->modules[CONF]->parameters[module_num].value = index;
    // CONF and PLAY text page
    byte offsetInPage = 
        myModules->modules[CONF]->parameters[module_num].cursor_pos;
    for (int i = 0; i < 4; i++) {
        myModules->modules[CONF]->text[i + offsetInPage + 3] = 
            names[index][i];
        myModules->modules[PLAY]->text[i + offsetInPage + 3] = 
            names[index][i];
    }
    if(myModules->modules[TIME + module_num]->size == 0) {
        return;
    }
    // and then data
    for(int i = 0; i < 4; i++) {
        myModules->modules[TIME + module_num]->io[i].value =
            readEEPROM(eeprom, offset++);
    }
    for(int i = 0; i < myModules->modules[TIME + module_num]->size; i++) {
        myModules->modules[TIME + module_num]->parameters[i].value =
            readEEPROM(eeprom, offset++);
    }
}

/**
 * @brief Write default values (factory preset) in the first slot.
 */

void write_factory() {
    byte data[8 * CONFIG_SIZE] = {
        0, 2, 3, 0, 0, 30,   3,  1,  0,  0,  0,  0,  0, // TIME
        4, 2, 4, 0, 2, 16,   1,  4,  0,  0,  0, 48,  0, // DRUM
        1, 2, 5, 1, 3,  3,   1, 24, 28, 31, 35, 38, 41, // BASS 
        5, 3, 6, 2, 4,  4,   1,  0,  0,  0,  0,  0,  0, // SEQ 
        2, 2, 7, 3, 5,  4,   1,  0,  0,  0, 24, 72,  0, // RAND
        6, 0, 0, 0, 0,  0,   0,  0,  0,  0,  0,  0,  0, // NONE
        6, 0, 0, 0, 0,  0,   0,  0,  0,  0,  0,  0,  0, // NONE
        6, 0, 0, 0, 0,  0,   0,  0,  0,  0,  0,  0,  0  // NONE
    };
    byte temp;
    for(int i = 0; i < 8 * CONFIG_SIZE; i++) {
        updateEEPROM(eeprom, i, data[i]);
    }
}

/**
 * @brief Write simple the second slot.
 */

void write_simple() {    
    byte data[8 * CONFIG_SIZE] = {
        0, 1, 2, 0, 0, 30,   3,  1,  0,  0,  0,  0,  0, // TIME
        3, 3, 2, 1, 3,  0, 108,  0,  0,  0,  0,  0,  0, // REDIR
        3, 4, 2, 2, 4,  0, 108,  0,  0,  0,  0,  0,  0, // REDIR
        3, 5, 2, 3, 5,  0, 108,  0,  0,  0,  0,  0,  0, // REDIR
        6, 0, 0, 0, 0,  0,   0,  0,  0,  0,  0,  0,  0, // NONE
        6, 0, 0, 0, 0,  0,   0,  0,  0,  0,  0,  0,  0, // NONE
        6, 0, 0, 0, 0,  0,   0,  0,  0,  0,  0,  0,  0, // NONE
        6, 0, 0, 0, 0,  0,   0,  0,  0,  0,  0,  0,  0  // NONE
    };
    int offset = 8 * CONFIG_SIZE;
    byte temp;
    for(int i = 0; i < 8 * CONFIG_SIZE; i++) {
        updateEEPROM(eeprom, offset++, data[i]);
    }

}

/**
 * @brief Write null values (factory preset) in the other slot.
 */

void write_null(int id) {
    int offset = 8 * CONFIG_SIZE * id;
    for(int i = 0; i < 8 * CONFIG_SIZE; i++) {
        if(i % CONFIG_SIZE == 0) {
            updateEEPROM(eeprom, offset++, 6);
        } else {
            updateEEPROM(eeprom, offset++, 0);
        }
    }
}

/**
 * @brief Print serial preset to test.
 */

void serial_data(byte module_num) {
    Module *m = myModules->modules[TIME + module_num];
    Serial.print(m->indexInList);
    Serial.print(", ");
    for(int i = 0; i < 4; i++) {
        Serial.print(m->io[i].value);
        Serial.print(", ");
    }
    for(int i = 0; i < m->size; i++) {
        Serial.print(m->parameters[i].value);
        Serial.print(", ");
    }
    for(int i = m->size; i < 8; i++) {
        Serial.print("0, ");
    }
    Serial.println();
}
