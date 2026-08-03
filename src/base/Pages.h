/**
 * @file Pages.h
 * @brief Classe utile pour l'affichage.
 */
#ifndef PAGE_H
#define PAGE_H
#include <Arduino.h>

typedef struct {
    char text[64]; /**<Chaîne affichée. */
    byte size; /**<Nombre d'items. */
    byte pos[8]; /**<Positions possibles du curseur. */
    byte cursor_num = 0; /**<Numéro d'item pointé par le curseur. */ 
} page;

class Pages {
    public:
        byte size; /**<Nombre de pages. */
        static page pages[16]; /**<Liste des pages. */
        static byte current_page_num; /**<Numéro de la page affichée. */
        Pages();
        void add(page p);
        void init();
        void test();
};
#endif
