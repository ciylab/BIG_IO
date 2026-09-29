# include <SPI.h>

const int PIN_CS = PC15; // Broche Chip Select

void setup() {
  pinMode(PIN_CS, OUTPUT);
  digitalWrite(PIN_CS, HIGH);
  SPI.begin();
}

void loop() {
  // Faire varier la valeur de 0 à 4095 (12 bits)
  for (int value = 0; value < 4096; value += 256) {
    writeDAC(value);
    delay(200);
  }
}

void writeDAC(unsigned int value) {
  // Configuration pour le MCP4921 :
  // Bit 15 = 0 (DAC A)
  // Bit 14 = 0 (Buffered)
  // Bit 13 = 1 (Gain 1x)
  // Bit 12 = 1 (Active mode / Shut down = 1)
  byte highByte = (1 << 3) | (1 << 2) | ((value >> 8) & 0x0F);
  byte lowByte = value & 0xFF;

  digitalWrite(PIN_CS, LOW);
  SPI.transfer(highByte);
  SPI.transfer(lowByte);
  digitalWrite(PIN_CS, HIGH);
}

