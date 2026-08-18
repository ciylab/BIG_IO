/**
 * @file dac.h
 * @brief Déclaration des fonctions de gestion des dacs.
 */

#ifndef DAC_H
#define DAC_H
#include <Arduino.h>

#define CS1 PA4    //!< Sortie du double DAC.
#define CS2 PC15   //!< Sortie du simple DAC.

/**
 * @brief Déclaration des pins de sorties et lancement de SPI.
 */
void init_dac();

/**
 * @brief Fonction d'écriture sur le bus SPI.
 *
 *  Build the 16-bit command word:\n
 *  Bit 15: A/B (0 for MCP4921)\n
 *  Bit 14: Buffered VREF (0 = unbuffered, 1 = buffered)\n
 *  Bit 13: Output Gain (1 = 1x, 0 = 2x)\n
 *  Bit 12: Shutdown control (1 = active operation)\n
 *  Bits 11-0: 12-bit data value\n
 *
 * @param ch l'un des trois canaux
 * @param cv un entier entre 0 et 4095
 */
void dac_write(byte ch, int cv);

/**
 * @brief Cette fonction permet de calibrer les CVs.
 *
 * La fonction permet d'envoyer exactement 4 volts pour C4 sur CV1.
 * On doit observer 2 volts sur CV2 et 1 volt sur CV3. La valeur est
 * conservée en mémoire dans les paramètres et sert de valeur de 
 * référence dans les actions.
 * @param val est la valeur récupérée. Pour val = 0
 *        la valeur de retour est l'entier correspondant
 *        à 4 volts.
 */
unsigned int calibrate(byte val);
#endif
