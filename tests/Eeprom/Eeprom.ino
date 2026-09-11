#include <Wire.h>

#define EEPROM 0x50
#define CONFIG_SIZE 13
#define CHUNK_SIZE 32
#define PAGE_SIZE 64

byte data[1000];

void writeEEPROM(int deviceaddress, unsigned int eeaddress, byte data) {
    Wire.beginTransmission(deviceaddress);
    Wire.write((int)(eeaddress >> 8));      //writes the MSB
    Wire.write((int)(eeaddress & 0xFF));    //writes the LSB
    Wire.write(data);
    Wire.endTransmission();
    delay(5); // important!
}

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

void read_eeprom(int deviceaddress, unsigned int begin, int length) {
    byte b;
    for(int i = 0; i < length; i++) {
        b = readEEPROM(deviceaddress, begin + i);
        print_format(b);
        if((i + 1) % 32 == 0) { 
            Serial.println();
        }
    }
    Serial.println();
}

void write_zero(int deviceaddress, unsigned int begin, 
        int length, byte *data) {
    for(int i = 0; i < length; i++) {
        writeEEPROM(deviceaddress, begin + i, 0);
    }
}

void setup() {
    Serial.begin(9600);
    Wire.begin();
    /*
    for(int i = 0; i < 3 * PAGE_SIZE; i++) {
        data[i] = i % 256;
    }
    write_zero(EEPROM, 0, 3 * PAGE_SIZE, data);
    writeByChunkEEPROM(EEPROM, 16, data, 114);
    */
}

void loop() {
    //  Nothing to do during loop
    delay(5000);
    read_eeprom(EEPROM, 8992, 7);
}


