/**
 * @file Module.h
 * @brief Déclaration de la classe.
 *
 * La plage de notes est celle d'un clavier de 88 touches.
 */

#ifndef MODULE_H
#define MODULE_H
#include "config.h"
#include "Display.h"

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
    parameter parameters[8]; /**<tableau des paramètres */
    int size; /**<nombre de paramètres */
    char name[8]; /**<nom du module */
    char text[64]; /**<texte de la page */
    Module();      // do nothing but needed
    Module(char *);
    void add(parameter p);
    void setMenu();
    virtual void handleNoteOn(byte channel, byte pitch, byte velocity) {};
    virtual void handleNoteOff(byte channel, byte pitch, byte velocity) {};
    /** pour afficher la valeur */
    virtual void getString(int val, char temp[8]) {};
    virtual void handleClock() {};
};

#endif
 
