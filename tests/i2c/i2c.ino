#include <Wire.h> 

void work() {
    delay(500);
    for (byte address = 1; address < 127; address++) { 
        Wire.beginTransmission(address); 
        byte error = Wire.endTransmission(); 
        if (error == 0) { 
            Serial.print("0x"); 
            if (address < 16) 
                Serial.print("0"); 
            Serial.println(address, HEX); 
        } 
    } 
}

void setup() { 
    Serial.begin(115200); 
    Wire.begin(); 
} 

void loop() {
    work();
}


