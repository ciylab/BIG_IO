/**
 * @file Display.h
 * @brief Champs de la classe d'affichage.
 */
 

#ifndef DISPLAY_H
#define DISPLAY_H

#include "config.h"

class Display {
    public:
        static byte cursor_num; /**< Index de 0 à 7 du curseur dans la liste. */
        static byte cursor_pos; /**< Position de 0 à 63 du curseur à l'écran. */
        static byte current_page; /**< id de la page courante. */
        static char buffer[64]; /**<tampon de l'écran */ 
        char screen[64]; /**<contenu de l'écran */
        static byte charIndex; /**<position dans le tampon */
        static byte endPosition; /**<dernière position à afficher */
        Display();
        void begin();
        void static putChar(byte position, char c);
        void welcome();
        void display();
        void static newPage();
        void static show_value(int val);
        void static no_show_value(parameter p); 
};

#endif
