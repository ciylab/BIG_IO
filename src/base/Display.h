/**
 * @file Display.h
 * @brief Champs de la classe d'affichage.
 */
 

#ifndef DISPLAY_H
#define DISPLAY_H
#include "Pages.h"

class Display {
  public:
    static char buffer[64]; /**<tampon de l'écran */ 
    char screen[64]; /**<contenu de l'écran */
    static byte charIndex; /**<position dans le tampon */
    static byte endPosition; /**<dernière position à afficher */
    Display();
    void begin();
    void static putChar(byte position, char c);
    void welcome();
    void display();
    void static new_config_page();
    void static newPage(byte index);
    void static show_config_values(byte j, byte index, int val);
    void static show_value(byte i, byte j, byte index, int val);
    void static no_show_value(byte index); 
    void static buildPlayPage();
};

#endif
