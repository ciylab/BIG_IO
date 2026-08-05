/**
 * @file Page.cpp
 * @brief Constructeurs.
 */
#include <Arduino.h>
#include "Pages.h"

byte Pages::current_page_num = 0;
page Pages::pages[16]; /**<Liste des pages. */

/**
 * Constructeur vide.
 */
Pages::Pages(){
    this->size = 0;
};

/**
 * Fonction pour ajouter une page à la collection.
 */
 
void Pages::add(page p) {
    pages[size] = p;
    size++;
}

/**
 * Fonction pour construire la collection.
 */
 
void Pages::init() {
    this->add({ // main page
            " CONFIG          CALIBR          PLAY            LOAD    SAVE", 
            5, {0, 16, 32, 48, 56}});
    this->add({ // config page
            " ID              IN              OUT             ACTION      ", 
            4, {0, 16, 32, 48}});
    this->add({ // play page
            " 1:      2:      3:      4:      5:      6:      7:      8:   ",
            8, {0, 8, 16, 24, 32, 40, 48, 56}});
}

void Pages::test() {
    delay(5000);
    for (int i = 0; i < this->size; i++) {
        page p = this->pages[i];
        Serial.print(p.size);
        Serial.print(" :");
        for(int j = 0; j < p.size; j++) {
            Serial.print(" ");
            Serial.print(p.pos[j]);
        }
        Serial.println();
        Serial.println(p.text);
    }
}
