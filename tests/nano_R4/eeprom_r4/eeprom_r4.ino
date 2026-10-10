#include <EEPROM.h>
#define CONFIG_SIZE 13
#define MEM_SIZE 768
#define QUARTER 24
#define LOOPER 5

/* 
 * Un total de 8 configurations en mémoire.
 * Une configuration = 8 x 13 bytes :
 * - 8 modules
 * Un module = 13 bytes:
 * - 1 numéro de type
 * - 4 paramètres d'entrée/sortie
 * - 8 paramètres maximum
 * Un total de 8 x 8 x 13 = 832 bytes. 
 * Il reste 8 x 1024 - 832 = 7360. Pour sauver une séquence de 4 mesures
 * on a besoin de 4 * 16 * 6 * 2 = 768 bytes sans la vélocité.
 * On choisit de pouvoir réserver au moins une séquence par slot. 
 * Donc un total de 8 séquences. Il reste 7360 - 8 x 768 = 1216 bytes.
 */

void print_format(byte b) {
    if(b < 10) {
        Serial.print("   ");
    } else if (b < 100) {
        Serial.print("  ");
    } else {
        Serial.print(" ");
    }
    Serial.print(b);
}

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
    int offset = 0;
    for(int i = 0; i < 8 * CONFIG_SIZE; i++) {
        EEPROM.update(offset++, data[i]);
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
        EEPROM.update(offset++, data[i]);
    }
}

void init_eeprom() {
    write_simple();              // SLOT A
    for(int i = 1; i < 9; i++) {
        write_null(i);           // SLOT B to H
    }
}

int getSequenceOffset(int mem_num) {
    return 8 * CONFIG_SIZE + MEM_SIZE * mem_num;
}

void example_1() {
    int length = 4; // a quarter note
    int pitch[4] = {24, 48, 36, 31};
    int offset = getSequenceOffset(0); // first memory
    for(int i = 0; i < length * 6; i++) { // note on
        if(i % 6 == 0) {
            EEPROM.update(offset++, pitch[i / 6]);
        } else {
            EEPROM.update(offset++, 0);
        }
    }
    for(int i = 0; i < length * 6; i++) { // note off
        if(i % 6 == 3) {
            EEPROM.update(offset++, pitch[i / 6]);
        } else {
            EEPROM.update(offset++, 0);
        }
    }
}

void print_mem(int mem_num) {
    byte b;
    Serial.print("************** BEGIN MEM ");
    Serial.println(mem_num);
    int offset = getSequenceOffset(mem_num);
    for(int i = 0; i < MEM_SIZE; i++) {
        b = EEPROM.read(offset + i);
        print_format(b);
        if((i + 1) % QUARTER == 0) {
            Serial.println();
        }
    }
    Serial.println("************** END MEM ");
}

int getSlotOffset(int slot_num) {
    return 8 * CONFIG_SIZE * slot_num;
}

void print_slot(int slot_num) {
    byte b;
    byte seq_num = 255;
    bool isLooper = false;
    Serial.print("***************** SLOT ");
    Serial.println(slot_num);
    int offset = getSlotOffset(slot_num);
    for(int i = 0; i < CONFIG_SIZE * 8; i++) {
        b = EEPROM.read(offset + i);
        print_format(b);
        if(i % CONFIG_SIZE == 0 && b == LOOPER) {
            isLooper = true;
        }
        if((i + 1) % CONFIG_SIZE == 0){
            Serial.println();
            if(isLooper) {
                print_mem(b);
            }
            isLooper = false;
        }
    }
    Serial.println();
    delay(1000);
}

void setup() {
    Serial.begin(9600);
    //init_eeprom();
    //example_1();
}

void loop() {
    for(int i = 0; i < 8; i++) {
        print_slot(i);
    } 
}


