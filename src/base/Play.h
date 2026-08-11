/**
 * @file Play.h
 * @brief Fonctions pour la page des algos.
 */
#ifndef PLAY_H
#define PLAY_H
#include "../base/Module.h"
#include "../base/Modules.h"

extern char *actions[8];
extern Modules *myModules;

class Play: public Module {
    public:
        /**
         * @brief Constructeur par défauti.
         *
         * Le bpm est compris entre 30 et 240 (Arturia keystep)
         * */
        Play(char name[8]) : Module(name) {
            this->add({" 1:    ", 0, 0, 0, 7, 0});
            this->add({" 2:    ", 0, 0, 0, 7, 8});
            this->add({" 3:    ", 0, 0, 0, 7, 16});
            this->add({" 4:    ", 0, 0, 0, 7, 24});
            this->add({" 5:    ", 0, 0, 0, 7, 32});
            this->add({" 6:    ", 0, 0, 0, 7, 40});
            this->add({" 7:    ", 0, 0, 0, 7, 48});
            this->add({" 8:    ", 0, 0, 0, 7, 56});
            this->setMenu();
        }
        void getString(int val, char temp[8]) {
            sprintf(temp, " %d:%.4s", 
                    Display::cursor_num + 1, actions[val]);
            temp[7] = '\0';
        }
        void l_handlePress() {
            Modules::current = MAIN;
            Display::newPage();
        }
        void r_handlePress() {
            Module *m = myModules->modules[Display::cursor_num + 3];
            if(m->size == 0) {
                return;
            }
            Modules::current = Display::cursor_num + 3;
            Display::newPage();
        }
};

#endif

