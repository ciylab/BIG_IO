#include <Arduino.h> // pour les tests avec Serial
#include "Display.h"
#include "config.h"
#include "dac.h"
#include "eeprom.h"
#include "Modules.h"

//extern Module *modules[3];
extern Modules *myModules;
extern algo algos[8];

/**
 * @file encoder.cpp
 * @brief Comportement général des deux encodeurs.
 * 
 * Les appels sont antérieurs aux autres appels.
 *
 */

/**
 * @brief Rotation de l'encodeur PARAMETER.
 *
 * Déplacement du curseur dans tous les cas
 * et affichage du paramètre précédent dans le cas d'un
 * algorithme à la place d'une éventuelle valeur. 
 *
 * Chaque rotation indique un nouveau choix.
 *
 */
bool new_value = false;

void l_handleRotate(int8_t rotation) {
    Module *m = myModules->modules[Modules::current];
    Display::putChar(Display::cursor_pos, ' ');
    if(new_value) {
        Display::no_show_value(m->parameters[Display::cursor_num]);
        new_value = false;
    }
    byte index = Display::cursor_num + m->size;
    if(0 < rotation) {
        index++;
    } else {
        index--;
    }
    Display::cursor_num = index % m->size;
    Display::cursor_pos = m->parameters[Display::cursor_num].cursor_pos;
    Display::putChar(Display::cursor_pos, '>');
}

/**
 * @brief Pression de l'encodeur PARAMETER.
 *
 * Alternance menu principal/algorithme.
 * Dans tous les cas, on rafraîchit toute la page.
 */

void l_handlePress() {
    if(Modules::current == TIME || Modules::current == PLAY) {
        Modules::current = MAIN; 
        Display::newPage();
    }
}

/**
 * @brief Pression longue de l'encodeur PARAMETER.
 *
 * Reboot.
 */

void l_handleLongPress() {
    NVIC_SystemReset();
}

/**
 * @brief Change la valeur par rotation.
 */

void change_value(int8_t rotation) {
    parameter *p;     
    p = &(myModules->modules[Modules::current]->parameters)[Display::cursor_num];
    if(!new_value && Modules::current != PLAY) {
        new_value = true;
        Display::show_value(p->value);
        return;
    }
    if(0 < rotation && p->value < p->max) {
        p->value++;
    } else if(rotation < 0 && p->min < p->value) {
        p->value--;
    } else {
        return; // nothing to do
    }
    Display::show_value(p->value);
    if(Modules::current == MAIN && Display::cursor_num == 1) {
        calibrate(p->value);
    } else if(Modules::current == PLAY) {
        algos[Display::cursor_num].action = p->value;
    }
}

/**
 * @brief Rotation de l'encodeur VALUE.
 *
 * Actif uniquement sur la page des algorithmes.
 * La première utilisation ne fait qu'afficher la valeur.
 * Les suivantes appellent la fonction du module. 
 */

void r_handleRotate(int8_t rotation) {
    if(Modules::current == MAIN) {
        switch(Display::cursor_num) {
            case 0:
                Modules::current = TIME; 
                Display::newPage();
                break; 
            case 2:
                Modules::current = PLAY; 
                Display::newPage();
                break;
            default:
                change_value(rotation);
        }
    } else {
        change_value(rotation);
    } 
}

/**
 * @brief Pression de l'encodeur VALUE.
 *
 * Actif uniquement sur la page des algorithmes.
 * La première utilisation ne fait qu'afficher la valeur.
 * Les suivantes appellent la fonction du module.
 */

void r_handlePress() {
    byte i = Modules::current;
    byte j = Display::cursor_num;
    parameter p = myModules->modules[i]->parameters[j];
    if(i == MAIN) { // main page
        if (j == 3) { //load
            load(p.value);
        } else if (j == 4) { //save
            save(p.value);
        }
    }
}
