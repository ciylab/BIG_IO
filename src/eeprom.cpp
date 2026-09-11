/**
 * @file eeprom.cpp
 */
#include <Wire.h>
#include "eeprom.h"
#include "Modules.h"
#include "midi.h"
#include "modules/Looper.h"

#define EEPROM 0x50
#define CHUNK_SIZE 32

/**
 * @brief for Serial output during test.
 */
#define SEP " "

/**
 * @see BIG_IO.ino
 */
extern Modules *myModules;

/**
 * @brief basic write
 */
void writeEEPROM(int deviceaddress, unsigned int eeaddress, byte data) {
    Wire.beginTransmission(deviceaddress);
    Wire.write((int)(eeaddress >> 8));      //writes the MSB
    Wire.write((int)(eeaddress & 0xFF));    //writes the LSB
    Wire.write(data);
    Wire.endTransmission();
    delay(5); // important!
}

/**
 * @brief basic read
 */
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

/**
 * @brief basic update
 *
 * Better than write.
 */
void updateEEPROM(int deviceaddress, unsigned int eeaddress, byte data) {
    byte temp;
    temp = readEEPROM(deviceaddress, eeaddress);
    if (temp != data) {
        writeEEPROM(deviceaddress, eeaddress, data);
    }
}

/**
 * @brief Write data by chunk (2 chunks of 32 bytes by page of 64 bytes)
 */
void writeByChunkEEPROM(int deviceaddress, unsigned int eeaddress, 
        byte *data, int length) {
    while(0 < length && eeaddress % CHUNK_SIZE != 0) {
        updateEEPROM(deviceaddress, eeaddress, data[eeaddress]);
        eeaddress++;
        length--;
    }
    while(CHUNK_SIZE <= length) {
        Wire.beginTransmission(deviceaddress);
        Wire.write((int)(eeaddress >> 8));      //writes the MSB
        Wire.write((int)(eeaddress & 0xFF));    //writes the LSB
        Wire.write(&data[eeaddress], CHUNK_SIZE);
        Wire.endTransmission();
        delay(5); // important!
        length = length - CHUNK_SIZE;
        eeaddress = eeaddress + CHUNK_SIZE;
    }
    while(0 < length) {
        updateEEPROM(deviceaddress, eeaddress, data[eeaddress]);
        eeaddress++;
        length--;
    }
}

/**
 * @brief Factory init
 */
void init_eeprom() {
    write_factory(); // FACT
    write_simple();  // SLOT A
    for(int i = 2; i < 8; i++) {
        write_null(i); // SLOT B to G
    }
}

void init_from_eeprom() {
    Wire.begin();
    //init_eeprom();
    load(0); // load from factory preset FACT.
}

void save_sequence(byte slot_num, byte module_num) {
    Module *m = myModules->modules[TIME + module_num];
    byte data[6];
    unsigned int offset;
    int i;
    int count = 0;
    offset = 8 * CONFIG_SIZE * 8;     // base config memory
    offset += 15 * 32 * 8 * slot_num; // slots memory for seq.
    offset += 15 * 32 * module_num;   // modules memory for seq.
    for(i = 0; i < 6 * m->parameters[0].value; i++) {
        if(count == 0) {
            Serial.println("**************** chunk");
            Wire.beginTransmission(EEPROM);
            Wire.write((int)(offset >> 8));      //writes the MSB
            Wire.write((int)(offset & 0xFF));    //writes the LSB
        }
        if(m->getData(i, data)) {
            Serial.print(data[0]);
            Serial.print(" ");
            Serial.print(data[1]);
            Serial.print(" ");
            Serial.print((data[2] << 8) + data[3]);
            Serial.print(" ");
            Serial.print((data[4] << 8) + data[5]);
            Serial.println();
            Wire.write(data, 6);
            count++;
            offset += 6;
        }
        if(count == 5) {
            Wire.endTransmission();
            delay(5); // important!
            count = 0;
            offset += 2;
        }
    }
    if(0 < count) {
        Wire.endTransmission();
        delay(5); // important!
    }
    /**
     * We write the null byte to mark the end.
     */
    Wire.beginTransmission(EEPROM);
    Wire.write((int)(offset >> 8));      //writes the MSB
    Wire.write((int)(offset & 0xFF));    //writes the LSB
    Wire.write(0);
    Wire.endTransmission();
    delay(5); // important!
}

void save_module(byte slot_num, byte module_num) {
    Module *m = myModules->modules[TIME + module_num];
    // The size of a slot is 8 * CONFIG_SIZE
    int offset = slot_num * 8 * CONFIG_SIZE + module_num * CONFIG_SIZE;
    writeEEPROM(EEPROM, offset++, m->indexInList);
    for(int i = 0; i < 4; i++) {
        updateEEPROM(EEPROM, offset++, m->io[i].value);
    }
    for(int i = 0; i < m->size; i++) {
        updateEEPROM(EEPROM, offset++, m->parameters[i].value);
    }
    for(int i = m->size; i < 8; i++) {
        updateEEPROM(EEPROM, offset++, 0);
    }
    if(m->indexInList == 5) { // LOOPER
        save_sequence(slot_num, module_num);
    }
}

void save(byte slot_num) {
    if(slot_num == 0) {
        return;
    }
    for(int i = 0; i < 8; i++) {
        save_module(slot_num, i);
        read_memory(i);
    }
}

void load(int slot_num) {    
    // the first byte address 
    int offset = 8 * slot_num * CONFIG_SIZE;
    for(int i = 0; i < 8; i++) {
        load_module_from_eeprom(offset + i * CONFIG_SIZE, i);
    }
}

void load_module_from_eeprom(int offset, byte module_num) {
    byte index = readEEPROM(EEPROM, offset++);
    myModules->load_module_from_memory(index, module_num);
    // and then data
    for(int i = 0; i < 4; i++) {
        myModules->modules[TIME + module_num]->io[i].value =
            readEEPROM(EEPROM, offset++);
    }
    for(int i = 0; i < myModules->modules[TIME + module_num]->size; i++) {
        myModules->modules[TIME + module_num]->parameters[i].value =
            readEEPROM(EEPROM, offset++);
    }
}

void write_factory() {
    byte data[8 * CONFIG_SIZE] = {
        0, 0, 1, 0, 1, 30,   3,  1,  0,  0,  0,  0,  0, // TIME
        4, 0, 2, 0, 2, 16,   1,  4,  0,  0,  0, 48,  0, // DRUM
        1, 0, 3, 1, 3,  3,   1, 24, 28, 31, 35, 38,  1, // BASS 
        5, 1, 4, 2, 4,  4,   1,  0,  0,  2,  0,  0,  0, // SEQ 
        2, 0, 5, 3, 5,  4,   1,  0,  0,  0,  0, 24, 72, // RAND
        6, 0, 0, 0, 0,  0,   0,  0,  0,  0,  0,  0,  0, // NONE
        6, 0, 0, 0, 0,  0,   0,  0,  0,  0,  0,  0,  0, // NONE
        6, 0, 0, 0, 0,  0,   0,  0,  0,  0,  0,  0,  0  // NONE
    };
    for(int i = 0; i < 8 * CONFIG_SIZE; i++) {
        updateEEPROM(EEPROM, i, data[i]);
    }
}

void write_simple() {    
    byte data[8 * CONFIG_SIZE] = {
        0, 0, 0, 0, 0, 30,   3,  1,  0,  0,  0,  0,  0, // TIME
        3, 3, 1, 1, 0,  0, 108,  0,  0,  0,  0,  0,  0, // REDIR
        3, 4, 2, 2, 0,  0, 108,  0,  0,  0,  0,  0,  0, // REDIR
        3, 5, 3, 3, 0,  0, 108,  0,  0,  0,  0,  0,  0, // REDIR
        6, 0, 0, 0, 0,  0,   0,  0,  0,  0,  0,  0,  0, // NONE
        6, 0, 0, 0, 0,  0,   0,  0,  0,  0,  0,  0,  0, // NONE
        6, 0, 0, 0, 0,  0,   0,  0,  0,  0,  0,  0,  0, // NONE
        6, 0, 0, 0, 0,  0,   0,  0,  0,  0,  0,  0,  0  // NONE
    };
    int offset = 8 * CONFIG_SIZE;
    for(int i = 0; i < 8 * CONFIG_SIZE; i++) {
        updateEEPROM(EEPROM, offset++, data[i]);
    }
}

void write_null(int slot_num) {
    byte data[8 * CONFIG_SIZE] = {
        0, 0, 1, 0, 0, 30,   3,  1,  0,  0,  0,  0,  0, // TIME
        6, 0, 0, 0, 0,  0,   0,  0,  0,  0,  0,  0,  0, // NONE
        6, 0, 0, 0, 0,  0,   0,  0,  0,  0,  0,  0,  0, // NONE
        6, 0, 0, 0, 0,  0,   0,  0,  0,  0,  0,  0,  0, // NONE
        6, 0, 0, 0, 0,  0,   0,  0,  0,  0,  0,  0,  0, // NONE
        6, 0, 0, 0, 0,  0,   0,  0,  0,  0,  0,  0,  0, // NONE
        6, 0, 0, 0, 0,  0,   0,  0,  0,  0,  0,  0,  0, // NONE
        6, 0, 0, 0, 0,  0,   0,  0,  0,  0,  0,  0,  0  // NONE
    };
    int offset = 8 * CONFIG_SIZE * slot_num;
    for(int i = 0; i < 8 * CONFIG_SIZE; i++) {
        updateEEPROM(EEPROM, offset++, data[i]);
    }
}

/**
 * @brief Serial print formatted byte with 3 chars only for test.
 */
void print_format(byte b) {
    if(b < 10) {
        Serial.print("  ");
    } else if (b < 100) {
        Serial.print(" ");
    }
    Serial.print(b);
}

void read_eeprom(int begin, int length) {
    byte b;
    for(int i = 0; i < length; i++) {
        b = readEEPROM(EEPROM, begin + i);
        print_format(b);
        Serial.print(SEP);
        if((i + 1) % CONFIG_SIZE == 0) { 
            Serial.println();
        }
    }
    Serial.println();
}

void read_memory(byte module_num) {
    Module *m = myModules->modules[TIME + module_num];
    Serial.println("******************** MEM");
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
