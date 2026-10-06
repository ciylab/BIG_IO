#include <EEPROM.h>
#define CONFIG_SIZE 14

/* 
 * Un total de 8 configurations en mémoire.
 * Une configuration = 8 x 14 bytes :
 * - 8 modules
 * Un module = 14 bytes:
 * - 1 numéro de type
 * - 4 paramètres d'entrée/sortie
 * - 8 paramètres maximum
 * - 1 adresse du premier byte pour le module SEQ
 * Un total de 8 x 8 x 14 = 896 bytes. 
 * Il reste 8 x 1024 - 896 = 7296. Pour sauver une séquence de 4 mesures
 * on a besoin de 4 * 16 * 6 * 2 = 768 bytes sans la vélocité.
 * On réserve une séquence par slot.
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
        0, 0, 1, 0, 1, 30,   3,  1,  0,  0,  0,  0,  0, 0, // TIME
        4, 0, 2, 0, 2, 16,   1,  4,  0,  0,  0, 48,  0, 0, // DRUM
        1, 0, 3, 1, 3,  3,   1, 24, 28, 31, 35, 38,  1, 0, // BASS 
        5, 1, 4, 2, 4,  0,   1,  0,  0,  2,  0,  0,  0, 8, // SEQ 
        2, 0, 5, 3, 5,  4,   1,  0,  0,  0,  0, 24, 72, 0, // RAND
        6, 0, 0, 0, 0,  0,   0,  0,  0,  0,  0,  0,  0, 0, // NONE
        6, 0, 0, 0, 0,  0,   0,  0,  0,  0,  0,  0,  0, 0, // NONE
        6, 0, 0, 0, 0,  0,   0,  0,  0,  0,  0,  0,  0, 0  // NONE
    };
}

void write_simple() {    
    byte data[8 * CONFIG_SIZE] = {
        0, 0, 0, 0, 0, 30,   3,  1,  0,  0,  0,  0,  0, 0, // TIME
        3, 3, 1, 1, 0,  0, 108,  0,  0,  0,  0,  0,  0, 0, // REDIR
        3, 4, 2, 2, 0,  0, 108,  0,  0,  0,  0,  0,  0, 0, // REDIR
        3, 5, 3, 3, 0,  0, 108,  0,  0,  0,  0,  0,  0, 0, // REDIR
        6, 0, 0, 0, 0,  0,   0,  0,  0,  0,  0,  0,  0, 0, // NONE
        6, 0, 0, 0, 0,  0,   0,  0,  0,  0,  0,  0,  0, 0, // NONE
        6, 0, 0, 0, 0,  0,   0,  0,  0,  0,  0,  0,  0, 0, // NONE
        6, 0, 0, 0, 0,  0,   0,  0,  0,  0,  0,  0,  0, 0  // NONE
    };
    int offset = 0;
    for(int i = 0; i < 8 * CONFIG_SIZE; i++) {
        EEPROM.update(offset++, data[i]);
    }
}

void write_null(int slot_num) {
    byte data[8 * CONFIG_SIZE] = {
        0, 0, 1, 0, 0, 30,   3,  1,  0,  0,  0,  0,  0, 0, // TIME
        6, 0, 0, 0, 0,  0,   0,  0,  0,  0,  0,  0,  0, 0, // NONE
        6, 0, 0, 0, 0,  0,   0,  0,  0,  0,  0,  0,  0, 0, // NONE
        6, 0, 0, 0, 0,  0,   0,  0,  0,  0,  0,  0,  0, 0, // NONE
        6, 0, 0, 0, 0,  0,   0,  0,  0,  0,  0,  0,  0, 0, // NONE
        6, 0, 0, 0, 0,  0,   0,  0,  0,  0,  0,  0,  0, 0, // NONE
        6, 0, 0, 0, 0,  0,   0,  0,  0,  0,  0,  0,  0, 0, // NONE
        6, 0, 0, 0, 0,  0,   0,  0,  0,  0,  0,  0,  0, 0  // NONE
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

void print_slot(int slot_num) {
    Serial.print("************************ ");
    Serial.println(slot_num);
    int offset = 8 * CONFIG_SIZE * slot_num;
    for(int i = 0; i < 14 * 8; i++) {
        if(i % 14 == 0 && i != 0){
            Serial.println();
        }
        print_format(EEPROM.read(offset + i));
    }
    Serial.println();
    delay(5000);
}

void setup() {
    Serial.begin(9600);
    //init_eeprom();
}

void loop() {
    for(int i = 0; i < 8; i++) {
        print_slot(i);
    } 
}


