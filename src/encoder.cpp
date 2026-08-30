/**
 * @file encoder.cpp
 */

#include <Arduino.h> // For Serial test 
#include "Display.h" // To display names and values
#include "dac.h"     // For calibrate
#include "Modules.h" // To change values

/**
 * The 12 modules.
 *
 * @see BIG_IO.ino file
 */
extern Modules *myModules;

void l_handleRotate(int8_t rotation) {
    Module *m = myModules->modules[Modules::current];
    Display::putChar(Display::cursor_pos, ' ');
    if(Modules::current == IO) {
        // On modifie les valeurs du module current mais
        // on est sur le module IO !
        if(myModules->modules[Modules::to_config]->new_value) {
            Display::show_name();
            myModules->modules[Modules::to_config]->new_value = false;
        }
    } else {
        if(m->new_value) {
            Display::show_name();
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
    Serial.print("Display::cursor_num : ");
    Serial.println(Display::cursor_num);
}

void l_handlePress() {
    myModules->modules[Modules::current]->l_handlePress();
}

void l_handleLongPress() {
    NVIC_SystemReset();
}

/**
 * @brief Change value except the first time.
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
        m->temp = p->value;
        return;
    }
    if(0 < rotation && m->temp < p->max) {
        m->temp++;
    } else if(rotation < 0 && p->min < m->temp) {
        m->temp--;
    } else {
        return; // nothing to do
    }
    Display::show_value(m->temp);
}

void r_handleRotate(int8_t rotation) {
    if(Modules::current == PLAY) {      // do nothing
        return;
    } 
    if(Modules::current == MAIN) {
        if(Display::cursor_num == 0) {  // go to CONF
            Modules::current = CONF;
            Display::newPage();
            return;
        }
        if(Display::cursor_num == 1) {  // go to PLAY
            Modules::current = PLAY; 
            Display::newPage();
            return;
        }
        if(Display::cursor_num == 4) {  // calibrate
            calibrate(rotation);
            return;
        }
    }
    change_value(rotation);
}

void r_handlePress() {
    if (3 < Modules::current) {
        Module *m = myModules->modules[Modules::current];
        parameter *p = &(m->parameters)[Display::cursor_num];
        if(m->new_value) {
            p->value = m->temp;
        }
    }
    myModules->modules[Modules::current]->r_handlePress();
}
