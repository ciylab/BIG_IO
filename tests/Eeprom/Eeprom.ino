//
//    FILE: I2C_small_eeprom_test.ino
//  AUTHOR: Tyler Freeman
// VERSION: 0.1.2
// PURPOSE: show/test I2C_EEPROM library with small EEPROMS
//     URL: https://github.com/RobTillaart/I2C_EEPROM
// HISTORY
// 0.1.0    2014-05-xx initial version
// 0.1.1    2020-07-14 fix #1 compile for ESP; fix author
// 0.1.2    2025-08-27 add print filename and version number of library


#include <Wire.h>
#include <I2C_eeprom.h>

#define TEST_ADDR 16
#define DEVICEADDRESS 0x50 

// #define SERIAL_DEBUG SerialUSB
#define SERIAL_DEBUG Serial

I2C_eeprom eeprom(DEVICEADDRESS, I2C_DEVICESIZE_24LC256);

void readAndWriteVar() {
    SERIAL_DEBUG.println("----------------------------------------------");
    SERIAL_DEBUG.print("SINGLE BYTE: writing and retreiving EEPROM on I2C at address ");
    SERIAL_DEBUG.println(DEVICEADDRESS);
    SERIAL_DEBUG.println("----------------------------------------------");

    byte curval = eeprom.readByte(TEST_ADDR);

    SERIAL_DEBUG.print("last value: ");
    SERIAL_DEBUG.println(curval);


    curval += 1;
    eeprom.writeByte(TEST_ADDR, curval);

    SERIAL_DEBUG.print("updating to: ");
    SERIAL_DEBUG.println(curval);
    delay(10);

    curval = eeprom.readByte(TEST_ADDR);
    SERIAL_DEBUG.print("new value: ");
    SERIAL_DEBUG.println(curval);
}




void setup()
{
  SERIAL_DEBUG.begin(57600);
  while (!SERIAL_DEBUG);  //  wait for SERIAL_DEBUG port to connect. Needed for Leonardo only
  SERIAL_DEBUG.println();
  SERIAL_DEBUG.println(__FILE__);
  SERIAL_DEBUG.print("I2C_EEPROM_VERSION: ");
  SERIAL_DEBUG.println(I2C_EEPROM_VERSION);
  SERIAL_DEBUG.println();

  SERIAL_DEBUG.println("IT IS BEGINNING");
  SERIAL_DEBUG.println("WAIT FOR IT");

  Wire.begin();

  eeprom.begin();

  readAndWriteVar();
  SERIAL_DEBUG.println("\nDone...");
}


void loop()
{
  //  Nothing to do during loop
}


