#include <Wire.h>

#define eeprom 0x50
#define CONFIG_SIZE 13

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

void read_eeprom_to(int length) {
    byte b;
    for(int i = 0; i < length; i++) {
        b = readEEPROM(eeprom, i);
        print_format(b);
        if((i + 1) % CONFIG_SIZE == 0) { 
            Serial.println();
        }
    }
    Serial.println();
}

void setup() {
    Serial.begin(9600);
    Wire.begin();
    delay(5000);
    read_eeprom_to(8 * CONFIG_SIZE);
}

void loop() {
    //  Nothing to do during loop
}


