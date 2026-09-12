/**
 * @file encoder.cpp
 */

#include "dac.h"     // For calibrate
#include "Modules.h" // To change values

/**
 * The 12 modules.
 *
 * @see BIG_IO.ino file
 */
extern Modules *myModules;

/**
 * @brief We move cursor.
 * 
 * After we show previous value or name
 */
void l_handleRotate(int8_t rotation) {
    Module *m = myModules->modules[Modules::current];
    if(Modules::current == IO) {
        // we use IO module but we show the
        // Modules::to_config io parameters !
        Module *other = myModules->modules[Modules::to_config];
        if(other->new_value) {
            parameter p = other->io[Display::cursor_num];
            Display::show_value(p.value);
            other->new_value = false;
        }
    } else if(m->new_value) {
        if(Modules::current == CONF) {
            parameter p = m->parameters[Display::cursor_num];
            Display::show_value(p.value);
        } else {
            Display::show_name();
        }
        m->new_value = false;
    }
    byte index = Display::cursor_num + m->size;
    if(0 < rotation) {
        index++;
    } else if(rotation < 0) {
        index--;
    }
    Display::moveCursor(index % m->size);
#ifdef DEBUG
    Serial.print("Display::cursor_num : ");
    Serial.println(Display::cursor_num);
#endif
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
    if(!m->new_value) {
        m->new_value = true;
        m->temp = p->value;
        if(Modules::current != CONF && Modules::current != IO) {
            Display::show_value(p->value);
            return; // no change, just show
        }
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
    if(3 < Modules::current || Modules::current == CONF) {
        Module *m = myModules->modules[Modules::current];
        parameter *p = &(m->parameters)[Display::cursor_num];
        if(m->new_value) {
#ifdef DEBUG
            Serial.println("******************** CONF");
            Serial.print("p->value : ");
            Serial.println(p->value);
            Serial.print("m->temp : ");
            Serial.println(m->temp);
#endif
            p->value = m->temp;
        }
    }
    myModules->modules[Modules::current]->r_handlePress();
}
