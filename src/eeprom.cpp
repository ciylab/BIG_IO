/**
 * @file eeprom.cpp
 */

#ifdef nanor4
#include <EEPROM.h>
#elif bluepill
#include <Wire.h>
#define EEPROM_ADDR 0x50
#endif
#include "eeprom.h"
//#include "Modules.h"

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
void writeEEPROM(unsigned int address, byte data) {
#ifdef nanor4
    EEPROM.write(address, data);
#elif bluepill
    Wire.beginTransmission(EEPROM_ADDR);
    Wire.write((int)(address >> 8));      // writes the MSB
    Wire.write((int)(address & 0xFF));    // writes the LSB
    Wire.write(data);
    Wire.endTransmission();
    delay(5);                               // important!
#endif
}

/**
 * @brief basic read
 */
byte readEEPROM(unsigned int address) {
    byte rdata;
#ifdef nanor4
    rdata = EEPROM.read(address);
#elif bluepill
    rdata = 0xFF;
    Wire.beginTransmission(EEPROM_ADDR);
    Wire.write((int)(address >> 8));
    Wire.write((int)(address & 0xFF));
    Wire.endTransmission();
    Wire.requestFrom(EEPROM_ADDR,1);
    if (Wire.available()) { 
        rdata = Wire.read();
    }
#endif
    return rdata;
}

/**
 * @brief basic update
 *
 * Better than write.
 */
void updateEEPROM(unsigned int address, byte data) {
    byte temp;
    temp = readEEPROM(address);
    if (temp != data) {
        writeEEPROM(address, data);
    }
}

/**
 * @brief Load default values (factory preset) in the first slot.
 */
void load_factory_preset() {
    byte data[8 * CONFIG_SIZE] = {
        0, 0, 1, 0, 1, 30,   3,  1,  0,  0,  0,  0,  0, // TIME
        4, 0, 2, 0, 2, 16,   1,  4,  0,  0,  0, 48,  0, // DRUM
        1, 0, 3, 1, 3,  3,   1, 24, 28, 31, 35, 38,  1, // BASS 
        5, 1, 4, 2, 4,  0,   1,  0,  0,  2,  0,  0,  0, // SEQ 
        2, 0, 5, 3, 5,  4,   1,  0,  0,  0,  0, 24, 72, // RAND
        6, 0, 0, 0, 0,  0,   0,  0,  0,  0,  0,  0,  0, // NONE
        6, 0, 0, 0, 0,  0,   0,  0,  0,  0,  0,  0,  0, // NONE
        6, 0, 0, 0, 0,  0,   0,  0,  0,  0,  0,  0,  0  // NONE
    };
    int offset = 0;
    for(int module_num = 0; module_num < 8; module_num++) {
        byte index = data[offset++];
        myModules->load_module_from_memory(index, module_num);
        Module *m = myModules->modules[TIME + module_num];
        for(int i = 0; i < 4; i++) {
            m->io[i].value = data[offset++];
        }
        for(int i = 0; i < 8; i++) {
            m->parameters[i].value  = data[offset++];
        }
    }
}

/**
 * @brief Write simple the second slot.
 */
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
    int offset = 0;
    for(int i = 0; i < 8 * CONFIG_SIZE; i++) {
        updateEEPROM(offset++, data[i]);
    }
}

/**
 * @brief Write null values (factory preset) in the other slot.
 *
 * @param slot_num slot num (> 2)
 */
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
        updateEEPROM(offset++, data[i]);
    }
}

/**
 * @brief Compute offset for sequence of data
 *
 * @param slot_num the slot number (FACT = 0)
 * @param module_num the module number (TIME = 0)
 */
unsigned int get_offset(byte slot_num, byte module_num) {
    unsigned int offset = 8 * CONFIG_SIZE * 8; // base config memory
    offset += 15 * 32 * 8 * slot_num;          // slots memory for seq
    offset += 15 * 32 * module_num;            // modules memory for seq
    return offset;
}

/**
 * @brief Set sequences to null for any module
 * 
 * The key is to set the end mark of sequence with data[0] = 0
 */
void init_data() {
    unsigned int offset;
    for(byte slot_num = 0; slot_num < 8; slot_num++) {
        for (byte module_num = 0; module_num < 8; module_num++) {
            offset = get_offset(slot_num, module_num);
            updateEEPROM(offset, 0);
        }
    }
}

/**
 * @brief Factory presets init with null sequence
 */
void init_eeprom() {
    write_simple();              // SLOT A
    for(int i = 1; i < 8; i++) {
        write_null(i);           // SLOT B to H
    }
    //init_data();
}

/**
 * @brief Starting with the slot 0 of factory preset 
 *
 * @remark The user cannot write on this preset.
 */
void init_from_eeprom() {
#ifdef bluepill
    Wire.begin();
#endif
    // Only to put the values in eeprom from factory CIYLab.
    // init_eeprom();
    load(0); // load from factory preset FACT.
}

void print_data(byte data[6], int count_note) {
    if(count_note == 0) {
        Serial.println("**************** new chunk");
    }
    Serial.print(data[0]);
    if(data[0] != 0) {
        Serial.print(" ");
        Serial.print(data[1]);
        Serial.print(" ");
        Serial.print((data[2] << 8) + data[3]);
        Serial.print(" ");
        Serial.print((data[4] << 8) + data[5]);
    }
    Serial.println();
}

/**
 * @brief Get sequence from eeprom.
 *
 * @param m the LOOPER module
 */
void read_sequence(Module *m) {
    byte length = m->parameters[0].value;
    byte mem_num = m->parameters[5].value - 1;
    unsigned int offset = 
        8 * CONFIG_SIZE + mem_num * 2 * SEQ_SIZE;
    for(int i = 0; i < 6 * length; i++) {
        m->setData(i, readEEPROM(offset++));
    }
    for(int i = 0; i < 6 * length; i++) {
        m->setData(i + SEQ_SIZE, readEEPROM(offset++));
    }
}

/**
 * @brief Set sequence to eeprom by chunck of 30 bytes = 5 notes.
 *
 * @param slot_num the slot number (FACT = 0)
 * @param module_num the module number (TIME = 0)
 */
void write_sequence(byte slot_num, byte module_num) {
/*
    Module *m = myModules->modules[TIME + module_num];
    byte data[6];
    unsigned int offset = get_offset(slot_num, module_num);
    int i;
    int count_note = 0;
    int count_chunk = 0;
    Wire.beginTransmission(EEPROM);
    Wire.write((int)(offset >> 8)); 
    Wire.write((int)(offset & 0xFF));
    for(i = 0; i < 6 * m->parameters[0].value; i++) {
        if(m->getData(i, data)) {
#ifdef DEBUG
            print_data(data, count_note);
#endif
            Wire.write(data, 6);
            count_note++;
            offset += 6;
        }
        if(count_note == 5) {                    // 30 bytes
            Wire.endTransmission();
            delay(5);
            count_chunk++;
            count_note = 0;
            offset += 2;                         // jump 2 bytes
            Wire.beginTransmission(EEPROM);      // new chunk
            Wire.write((int)(offset >> 8));
            Wire.write((int)(offset & 0xFF));        
        }
    }
    if(0 < count_note) {
        Wire.endTransmission();
        delay(5);    
    }
    */
    /**
     * @brief We write the null byte to mark the end.
     *
     * @remark If the sequence is empty then the first byte is 0.
     */
     /*
    if(count_chunk < 15) {
        writeEEPROM(offset, 0);
    }*/
}

/**
 * @brief To save only one module
 *
 * @param offset firt byte num
 * @param module_num from 0 to 7
 */
void write_module(byte slot_num, byte module_num) {
    Module *m = myModules->modules[TIME + module_num];
    // The size of a slot is 8 * CONFIG_SIZE
    int offset = slot_num * 8 * CONFIG_SIZE + module_num * CONFIG_SIZE;
    writeEEPROM(offset++, m->indexInList);
    for(int i = 0; i < 4; i++) {
        updateEEPROM(offset++, m->io[i].value);
    }
    for(int i = 0; i < m->size; i++) {
        updateEEPROM(offset++, m->parameters[i].value);
    }
    for(int i = m->size; i < 8; i++) {
        updateEEPROM(offset++, 0);
    }
    if(m->indexInList == 5) { // LOOPER
        write_sequence(slot_num, module_num);
    }
}

void save(byte slot_num) {
    if(slot_num == 0) {
        return;
    }
    slot_num--;
    for(int i = 0; i < 8; i++) {
        write_module(slot_num, i);
        read_memory(i);
    }
}

/**
 * @brief load a module in memory from eeprom.
 * 
 * @param slot_num slot num from 0 to 7
 * @param module_num in the current modules from 0 to 7
 */
void read_module_from_eeprom(byte slot_num, byte module_num) {
    // the first byte address
    int offset = (8 * slot_num + module_num) * CONFIG_SIZE;
    byte index = readEEPROM(offset++);
    myModules->load_module_from_memory(index, module_num);
    Module *current = myModules->modules[TIME + module_num];
    // and then data
    for(int i = 0; i < 4; i++) {
        current->io[i].value = readEEPROM(offset++);
    }
    for(int i = 0; i < current->size; i++) {
        current->parameters[i].value = readEEPROM(offset++);
    }
    if(index == 5 // LOOPER
            && current->parameters[5].value != 0 // sequence in eeprom
      ) {
        read_sequence(current);
    }
}

void load(int slot_num) { 
    if (slot_num == 0) {
        load_factory_preset();
        return;
    }  
    slot_num--;
    for(int i = 0; i < 8; i++) {
        read_module_from_eeprom(slot_num, i);
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

/**
 * @brief Read data from eeprom for test
 *
 * @param begin the first byte
 * @param length number of bytes
 */
void read_eeprom(int begin, int length) {
    byte b;
    for(int i = 0; i < length; i++) {
        b = readEEPROM(begin + i);
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
