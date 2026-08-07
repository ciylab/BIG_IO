/**
 * @file Module.h
 * @brief Déclaration de la classe.
 *
 * La plage de notes est celle d'un clavier de 88 touches.
 */

#ifndef MODULE_H
#define MODULE_H
#include "config.h"

/** 
 * @brief Tableau des chaînes pour les barres de progression indiquant les %
 * d'aléatoire.
 *
 * Le caractère dollar est remplacé par un demi-rectangle plein 
 * et l'apostrophe par un rectangle plein.
 *
 */

class Module {
  public:
    byte out; /**<canal de sortie */
    parameter parameters[8]; /**<tableau des paramètres */
    int size; /**<nombre de paramètres */
    char name[8]; /**<nom du module */
    char text[64];
    Module();      // do nothing but needed
    Module(char *);
    void add(parameter p);
    void setMenu();
    void handleNoteOn(byte channel, byte pitch, byte velocity);
    void handleNoteOff(byte channel, byte pitch, byte velocity);
};

#endif
 
