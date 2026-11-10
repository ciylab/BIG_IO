#include <SPI.h>

#ifdef bluepill
#define CS1 PB0
#define CS2 PA3
#elif nanor4
#define CS1 D10
#define CS2 A0
#endif

// Fonction pour envoyer la valeur au MCP4921 (Valeur entre 0 et 4095)
void writeMCP4921(uint16_t valeur) {
    
    // Sécurise la valeur pour ne pas dépasser 12 bits (4095)
    valeur &= 0x0FFF; 

    // Ajoute les bits de configuration au début du message (4 bits de poids fort)
    // Bit 15 (0) : Sélection du canal A
    // Bit 14 (0) : VREF non bufferisé
    // Bit 13 (1) : Gain 1x (Sortie = VREF * Valeur / 4096)
    // Bit 12 (1) : Active la sortie (Pas de mode veille)
    uint16_t commande = 0x3000 | valeur;

    // Active le composant (CS passe à LOW)
    digitalWrite(CS1, LOW);

    // Envoie les 16 bits en deux fois (8 bits par 8 bits)
    SPI.transfer(highByte(commande));
    SPI.transfer(lowByte(commande));

    // Désactive le composant (CS passe à HIGH) pour valider l'écriture
    digitalWrite(CS1, HIGH);
}

void writeMCP4922(int canal, uint16_t valeur) {
    valeur &= 0x0FFF; 
    uint16_t commande = 0x3000 | valeur; 

    if (canal == 1) {
        commande |= 0x8000; // Sélectionne le canal B si canal == 1
    }

    digitalWrite(CS2, LOW);
    SPI.transfer(highByte(commande));
    SPI.transfer(lowByte(commande));
    digitalWrite(CS2, HIGH);
}

void setup() {
    pinMode(CS1, OUTPUT);
    pinMode(CS2, OUTPUT);
    digitalWrite(CS1, HIGH);
    digitalWrite(CS2, HIGH);    
#ifdef nanor4
    analogWriteResolution(12);
#endif
    SPI.begin();
    // Optionnel mais recommandé : configure la vitesse et le mode SPI
    SPI.beginTransaction(SPISettings(2000000, MSBFIRST, SPI_MODE0));
}

void loop() {
    // 1. Sortie au maximum (Environ 5V si VREF = 5V)
#ifdef bluepill
    // MCP4921
    writeMCP4921(4095);
#elif nanor4
    analogWrite(CS1, 4095);
#endif  
    writeMCP4922(1, 2000);        // Canal A
    writeMCP4922(0, 1000);        // Canal B
    delay(500); // Attend 1 seconde

    // 2. Sortie au minimum (0V)
#ifdef bluepill
    // MCP4921
    writeMCP4921(0);
#elif nanor4
    analogWrite(CS1, 0);
#endif 
    writeMCP4922(1, 0);        // Canal A
    writeMCP4922(0, 0);        // Canal B
    delay(500); // Attend 1 seconde
}
