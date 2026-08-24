/**
 * @file Conf.h
 * @brief Fonctions pour la page des input/output.
 */
#ifndef CONF_H
#define CONF_H
#include "Module.h"
#include "Modules.h"

extern Modules *myModules;
extern char *names[];

class Conf: public Module {
    public:
        /**
         * @brief Constructeur par défauti.
         *
         * Le bpm est compris entre 30 et 240 (Arturia keystep)
         * */
        Conf() : Module() {
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
            Modules::to_config = Display::cursor_num + TIME;
            myModules->modules[Modules::to_config]->new_value = false;
            Modules::current = IO;
            Display::newPage();
        }
};

#endif

