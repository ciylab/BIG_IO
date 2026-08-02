/**
 * @file Display.cpp
 * @brief Gestion de l'affichage.
 *
 * La variable screen représente ce qui est affiché.
 * La variable buffer est ce qui doit être affiché.
 * Pour des questions de latence, screen est mis à jour à partir
 * de buffer tant qu'elles sont différentes et un caractère
 * par boucle de loop(). 
 */


#include <U8x8lib.h>
#include "Display.h"
#include "Pages.h"

/**
 * Oled SSD1306 ou SH1106.
 */

U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(U8X8_PIN_NONE);

char Display::buffer[64];

byte Display::charIndex = 0; /**<position dans le tampon */
byte Display::endPosition = 63; /**<dernière position à afficher */

/**
 * @brief Initialisation avec 64 espaces.
 */
Display::Display() {
    for (int i = 0; i < 64; i++) {
        screen[i] = ' ';
    }
    screen[63] = '\0';
    u8x8.setFont(u8x8_font_7x14_1x2_r);
}

/**
 * @brief Initialisation du setup.
 */
void Display::begin() {
    u8x8.begin();
}
    
/**
 * @brief Affiche un caractère **c** à une position **position**.
 */
void Display::putChar(byte position, char c) {
    u8x8.drawGlyph(position % 16, 2 * (position / 16), c);
}

/**
 * @brief Affiche un message de bienvenue.
 */

void Display::welcome() {
    sprintf(screen, "  BIG InOut       MIDI/CV/GATE    BY CIYLAB       %s",
            VERSION);
    for (int i = 0; i < 63; i++) {
        putChar(i, screen[i]);
    }
}

/**
 * @brief Fonction de rafraîchissement.
 *
 * La variable **charIndex** est le numéro de caractère courant à afficher.
 * La variable **endPosition** est le numéro du dernier caractère du
 * buffer à afficher. En général il y a un groupe de 6 caractères seulement
 * à rafraîchir. La fonction en affiche un au maximum.
 * */

void Display::display() {
    // without buffer : 100ms
    // with buffer : 2ms
    if (endPosition <= charIndex) {
        return;
    }
    while (charIndex < endPosition && 
        screen[charIndex] == buffer[charIndex]) {
        charIndex++;
    }
    putChar(charIndex, buffer[charIndex]);
    screen[charIndex] = buffer[charIndex];
    charIndex++;
}

void Display::newPage(byte index) {
    sprintf(buffer, Pages::pages[Pages::current_page_num].text);
    charIndex = 0;
    endPosition = 63;
    putChar(index, ' ');
    putChar(0, '>');
}

void Display::show_value(byte index, int val) {
    charIndex = index;
    sprintf(buffer + index, " %3d    ", val);
    endPosition = index + 7;
}

void Display::no_show_value(byte index) {
    charIndex = index;
    endPosition = index + 7;
    for (int i = index; i < endPosition; i++) {
        buffer[i] = Pages::pages[Pages::current_page_num].text[i];
    }
}


