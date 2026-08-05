#include <Arduino.h> // pour les tests avec Serial
#include "Display.h"
#include "Pages.h"
#include "config.h"
#include "dac.h"
#include "eeprom.h"

extern data values[16][8];
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
    page *p;
    p = &Pages::pages[Pages::current_page_num];
    byte index = p->cursor_num;
    Display::putChar(p->pos[index], ' ');
#ifdef DEBUG
    Serial.print("page: ");
    Serial.print(Pages::current_page_num);
    Serial.print(" item: ");
    Serial.print(p->cursor_num);
#endif
    if(new_value) {
        Display::no_show_value(p->pos[index]);
        new_value = false;
    }
    index += p->size;
    if(0 < rotation) {
        index++;
    } else {
        index--;
    }
    p->cursor_num = index % p->size;
#ifdef DEBUG
    Serial.print(" ---> ");
    Serial.println(p->cursor_num);
#endif
    Display::putChar(p->pos[p->cursor_num], '>');
}

/**
 * @brief Pression de l'encodeur PARAMETER.
 *
 * Alternance menu principal/algorithme.
 * Dans tous les cas, on rafraîchit toute la page.
 */

void l_handlePress() {
#ifdef DEBUG
	Serial.println("Left Pressed");
#endif
    page p = Pages::pages[Pages::current_page_num];
    if(Pages::current_page_num == 1) {
        Pages::current_page_num = 0; 
        Display::newPage(p.pos[p.cursor_num]);
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
    byte i = Pages::current_page_num;
    page p = Pages::pages[i];
    byte j = p.cursor_num;
#ifdef DEBUG
    Serial.print("page: ");
    Serial.print(i);
    Serial.print(" item: ");
    Serial.print(j);
    Serial.print(" old val: ");
    Serial.print(values[i][j].val);
#endif
    if(!new_value) {
        new_value = true;
        Display::show_value(i, j, p.pos[j], values[i][j].val);
        if (i != 1) {
#ifdef DEBUG
            Serial.println(" no change");
#endif
            return;
        }
    }
    if(0 < rotation && 
            values[i][j].val < values[i][j].max) {
        values[i][j].val++;
    } else if(rotation < 0 && 
            values[i][j].min < values[i][j].val) {
        values[i][j].val--;
    } else {
        return; // nothing to do
    }
#ifdef DEBUG
    Serial.print(" new val: ");
    Serial.println(values[i][j].val);
#endif
    Display::show_value(i, j, p.pos[j], values[i][j].val);
    if(i == 0 && j == 1) { // calibration
        calibrate(values[i][j].val);
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
    page p = Pages::pages[Pages::current_page_num];
    if(Pages::current_page_num == 0) {
        switch(p.cursor_num) {
            case 0:
                Pages::current_page_num = 1; 
                Display::newPage(p.pos[p.cursor_num]);
                break; 
            case 2:
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
    byte i = Pages::current_page_num;
    page p = Pages::pages[i];
    byte j = p.cursor_num;
    if(i == 0) { // main page
        if (j == 3) { //load
            load(values[i][j].val);
        } else if (j == 4) { //save
            save(values[i][j].val);
        }
        values[1][0].val = 0; // we start from ID = 1
    }
#ifdef DEBUG
	Serial.print("slot : ");
    Serial.println(values[i][j].val);
#endif
}
