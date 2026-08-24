/**
 * @file Play.h
 * @brief Fonctions pour la page des algos.
 */
#ifndef PLAY_H
#define PLAY_H
#include "Module.h"
#include "Modules.h"

extern Modules *myModules;
extern char *names[];

class Play: public Module {
    public:
        /**
         * @brief Constructeur par défauti.
         *
         * Le bpm est compris entre 30 et 240 (Arturia keystep)
         * */
        Play() : Module() {
            this->size = 0;
            this->add({" 1:    ", 0, 0, 0, 0, 0});
            this->add({" 2:    ", 0, 0, 1, 5, 8});
            this->add({" 3:    ", 0, 0, 1, 5, 16});
            this->add({" 4:    ", 0, 0, 1, 5, 24});
            this->add({" 5:    ", 0, 0, 1, 5, 32});
            this->add({" 6:    ", 0, 0, 1, 5, 40});
            this->add({" 7:    ", 0, 0, 1, 5, 48});
            this->add({" 8:    ", 0, 0, 1, 5, 56});
            this->setMenu();
        }
        void getString(int val, char temp[8]) {
            sprintf(temp, " %d:%.4s", 
                    Display::cursor_num + 1, 
                    names[val]);
            temp[7] = '\0';
        }
        void l_handlePress() {
            Modules::current = MAIN;
            Display::newPage();
        }
        void r_handlePress() {
            Module *m = myModules->modules[Display::cursor_num + TIME];
            if(m->size == 0) {
                return;
            }
            m->new_value = false;
            Modules::current = Display::cursor_num + TIME;
            Display::newPage();
        }
};

#endif

