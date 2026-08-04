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
#include "config.h"

/**
 * Oled SSD1306 ou SH1106.
 */

U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(U8X8_PIN_NONE);

char Display::buffer[64];

byte Display::charIndex = 0; /**<position dans le tampon */
byte Display::endPosition = 63; /**<dernière position à afficher */
extern algo algos[8];
extern data values[16][8];

char *in[18] = {
    "NONE ", // 0
    "CH1  ", "CH2  ", "CH3  ", "CH4  ", // 1
    "CH5  ", "CH6  ", "CH7  ", "CH8  ", // 5
    "CH9  ", "CH10 ", "CH11 ", "CH12 ", // 9
    "CH13 ", "CH14 ", "CH15 ", "CH16 ", // 13
    "TRIG0"  // 17
};   

char *out[28] = {
    "NONE ", // 0
    "CH1  ", "CH2  ", "CH3  ", "CH4  ", // 1
    "CH5  ", "CH6  ", "CH7  ", "CH8  ", // 5
    "CH9  ", "CH10 ", "CH11 ", "CH12 ", // 9 
    "CH13 ", "CH14 ", "CH15 ", "CH16 ", // 13
    "TRIG1", "TRIG2", "TRIG3", "TRIG4", "TRIG5", // 17
    "CV1  ", "CV2  ", "CV3  ", // 22
    "CVGT1", "CVGT2", "CVGT3"  // 25
};

char *actions[9] = {
    "NONE",   // 0
    "ARPEG ", // 1
    "COMP  ", // 2
    "MINISQ", // 3
    "RAND  ", // 4
    "RECORD", // 5
    "SIMPLE", // 6
    "TIME  ", // 7
    "TRIG  "  // 8
};

char *memory[8] = {
    "FACT",   // 0
    "SLOT A", // 1
    "SLOT B", // 2
    "SLOT C", // 3
    "SLOT D", // 4
    "SLOT E", // 5
    "SLOT F", // 6
    "SLOT G" // 7
};

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

void Display::new_config_page() {
    int val = 0;
    byte idx = 0;
    values[1][1].val = algos[val].in;
    values[1][2].val = algos[val].out;
    values[1][3].val = algos[val].action_num;
    idx += 7;
    sprintf(buffer + idx, " %d    ", val + 1);
    idx += 16;
    sprintf(buffer + idx, " %s ", in[algos[val].in]);
    idx += 16;
    sprintf(buffer + idx, " %s ", out[algos[val].out]);
    idx += 16;
    sprintf(buffer + idx, " %s ", actions[algos[val].action_num]);
}

void Display::newPage(byte index) {
    page p = Pages::pages[Pages::current_page_num];
    sprintf(buffer, p.text);
    if(Pages::current_page_num == 1) {
        // exceptionnellement on affiche toutes les valeurs
        new_config_page();
    }
    charIndex = 0;
    endPosition = 63;
    putChar(index, ' ');
    putChar(0, '>');
}

void Display::show_config_values(byte j, byte index, int val) {
    charIndex = index;
    int num = values[1][0].val; // id parmi 8 des algos
    switch(j) {
        case 0:
            // on change les valeurs stockées par défaut.
            values[1][1].val = algos[val].in;
            values[1][2].val = algos[val].out;
            values[1][3].val = algos[val].action_num;
            index += 7;
            sprintf(buffer + index, " %d    ", val + 1);
            index += 16;
            sprintf(buffer + index, " %s ", in[algos[val].in]);
            index += 16;
            sprintf(buffer + index, " %s ", out[algos[val].out]);
            index += 16;
            sprintf(buffer + index, " %s ", actions[algos[val].action_num]);
            break;
        case 1:
            index += 7;
            algos[num].in = val;
            sprintf(buffer + index, " %s ", in[val]);
            break;
        case 2:
            index += 7;
            algos[num].out = val;
            sprintf(buffer + index, " %s ", out[val]);
            break;
        case 3:
            index += 7;
            algos[num].action_num = val;
            sprintf(buffer + index, " %s ", actions[val]);
            break;
    }
    endPosition = index + 7;
}

void Display::show_value(byte i, byte j, byte index, int val) {
    if (i == 1) {
        show_config_values(j, index, val);
        return;
    }
    charIndex = index;
    if (i == 0 && (j == 3 || j == 4)) {
        sprintf(buffer + index, " %s ", memory[val]);
    } else {
        sprintf(buffer + index, " %3d   ", val);
    }
    endPosition = index + 7;
}

void Display::no_show_value(byte index) {
    charIndex = index;
    endPosition = index + 7;
    for (int i = index; i < endPosition; i++) {
        buffer[i] = Pages::pages[Pages::current_page_num].text[i];
    }
}


