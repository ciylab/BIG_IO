/**
 * @file encoder.cpp
 * @brief Comportement général des deux encodeurs.
 * 
 * Les appels sont antérieurs aux autres appels. Les réponses 
 * spécifiques aux modules sont traités dans les classes filles.
 *
 */

#include <Arduino.h> // pour les tests avec Serial
#include "Display.h" // gére l'affichage du curseur sans buffer
#include "dac.h"     // pour le calibrage en temps réel
#include "Modules.h" // impacte forcément l'affichage pour les valeurs
/**
 *  Variable (très) locale bloquant le changement de valeur 
 *  lors du premier affichage.
 *  On tourne l'encodeur mais la valeur ne change pas.
 */
bool new_value = false;

extern Modules *myModules;

/**
 * @brief Rotation de l'encodeur de gauche pour naviguer sur la page.
 *
 * Déplacement du curseur dans tous les cas. 
 *
 * Chaque rotation indique un nouveau choix. Ici c'est cursor_num
 * qui est important : la valeur permet de positionner le curseur
 * et indique le paramètre concerné.
 *
 */


void l_handleRotate(int8_t rotation) {
    Module *m = myModules->modules[Modules::current];
    Display::putChar(Display::cursor_pos, ' ');
    if(Modules::current == IO) {
        // On modifie les valeurs du module to_config mais
        // on est sur le module IO !
        if(myModules->modules[Modules::to_config]->new_value) {
            Display::no_show_value(m->parameters[Display::cursor_num]);
            myModules->modules[Modules::to_config]->new_value = false;
        }
    } else {
        if(m->new_value) {
            Display::no_show_value(m->parameters[Display::cursor_num]);
            m->new_value = false;
        }
    }
    byte index = Display::cursor_num + m->size;
    if(0 < rotation) {
        index++;
    } else if(rotation < 0) {
        index--;
    }
    Display::cursor_num = index % m->size;
    Display::cursor_pos = m->parameters[Display::cursor_num].cursor_pos;
    Display::putChar(Display::cursor_pos, '>');
}

/**
 * @brief Pression de l'encodeur de gauche.
 *
 * Gérer au cas par cas suivant le module chargé.
 */

void l_handlePress() {
    myModules->modules[Modules::current]->l_handlePress();
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
 * @brief Change la valeur par rotation sauf au premier tour.
 */

void change_value(int8_t rotation) {
    Module *m;
    parameter *p;
    if(Modules::current == IO) {
        m = myModules->modules[Modules::to_config];
        p = &(m->io)[Display::cursor_num];
    } else {
        m = myModules->modules[Modules::current];
        p = &(m->parameters)[Display::cursor_num];
    }
    if(!m->new_value && 
            Modules::current != CONF && 
            Modules::current != PLAY) {
        m->new_value = true;
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
    // Ici on agit immédiatement = temps réel.
    if(Modules::current == MAIN && Display::cursor_num == 1) {
        Modules::C4RefVolt = calibrate(p->value);
    }
}

/**
 * @brief Rotation de l'encodeur de droite pour changer les valeurs
 * ou afficher la page sélectionnée.
 */

void r_handleRotate(int8_t rotation) {
    if(Modules::current == MAIN && Display::cursor_num == 0) {
        Modules::current = CONF; 
        Display::newPage();
    } else if(Modules::current == MAIN && Display::cursor_num == 2) {
        Modules::current = PLAY; 
        Display::newPage();
    } else if(Modules::current == PLAY) {
        return;
    } else {
        change_value(rotation);
    } 
}

/**
 * @brief Pression de l'encodeur de droite en général pour
 * valider un choix. Usage rare.
 */

void r_handlePress() {
    myModules->modules[Modules::current]->r_handlePress();
}
