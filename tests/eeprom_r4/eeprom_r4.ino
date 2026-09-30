#include <EEPROM.h>

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

void setup() {
    Serial.begin(9600);
    for(int i = 0; i < 32; i++) {
        //EEPROM.update(i, i % 256);
    }
}

void loop() {
    for(int i = 0; i < 32; i++) {
        if(i % 16 == 0 && i != 0){
            Serial.println();
        }
        print_format(EEPROM.read(i));
    }
    Serial.println();
    delay(5000);
}


