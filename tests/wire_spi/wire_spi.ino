
#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <U8g2lib.h> // Idéal pour l'OLED I2C sur STM32

// Initialisation OLED I2C Matériel (sur PB6/PB7 ou PB10/PB11 selon la config Wire)
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

const int dacCS = PB0; // Broche Chip Select pour le MCP4921

void setup() {
  // 1. Initialiser le SPI pour le MCP4921
  pinMode(dacCS, OUTPUT);
  digitalWrite(dacCS, HIGH);
  SPI.begin(); 
  // Optionnel sur STM32 : configure la vitesse et le mode SPI pour le DAC
  SPI.beginTransaction(SPISettings(20000000, MSBFIRST, SPI_MODE0));

  // 2. Initialiser l'I2C pour l'OLED
  // Sur STM32, vous pouvez forcer les broches I2C avant le begin si nécessaire :
  // Wire.setSDA(PB7);
  // Wire.setSCL(PB6);
  u8g2.begin();
}

void setMCP4921_Voltage(uint16_t value) {
  // Le MCP4921 est un DAC 12-bits (0 à 4095)
  value &= 0x0FFF; 
  
  // Bit 15: 0 (Ecriture vers le DAC A)
  // Bit 14: 0 (Buffered VREF)
  // Bit 13: 1 (Gain 1x)
  // Bit 12: 1 (Active Mode / SHDN désactivé)
  // Configuration = 0x3000
  uint16_t packet = 0x3000 | value;

  digitalWrite(dacCS, LOW);
  SPI.transfer16(packet);
  digitalWrite(dacCS, HIGH);
}

void loop() {
  // Exemple : Envoi d'une valeur au DAC
  setMCP4921_Voltage(2048); // Environ mi-tension de VREF

  // Exemple : Mise à jour de l'écran OLED
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.drawStr(0, 10, "DAC & OLED OK");
  u8g2.sendBuffer();
  
  delay(100);
}
