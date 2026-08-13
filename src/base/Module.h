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
        parameter parameters[9]; /**<tableau des paramètres dont un caché */
        int size; /**<nombre de paramètres */
        char name[8]; /**<nom du module */
        char text[64]; /**<texte de la page */
        bool hidden; /**<le paramètre caché est... caché. */
        /**
         *  Variable bloquant le changement de valeur 
         *  lors du premier affichage.
         *  On tourne l'encodeur mais la valeur ne change pas.
         */
        bool new_value;         
        Module();      // do nothing but needed
        Module(char *);
        void add(parameter p);
        void setMenu();
        virtual void handleNoteOn(byte channel, byte pitch, byte velocity) {} 
        virtual void handleNoteOff(byte channel, byte pitch, byte velocity) {}
        virtual void handleClock() {}
        virtual void handleStart() {}
        virtual void handleStop() {}
        virtual void l_handlePress();
        virtual void r_handlePress();
        /** pour afficher la valeur */
        virtual void getString(int val, char temp[8]) {}
        virtual void execute() {}

};

#endif

