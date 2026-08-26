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
            this->add({" 2:    ", 0, 0, 1, 6, 8});
            this->add({" 3:    ", 0, 0, 1, 6, 16});
            this->add({" 4:    ", 0, 0, 1, 6, 24});
            this->add({" 5:    ", 0, 0, 1, 6, 32});
            this->add({" 6:    ", 0, 0, 1, 6, 40});
            this->add({" 7:    ", 0, 0, 1, 6, 48});
            this->add({" 8:    ", 0, 0, 1, 6, 56});
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
            byte index = this->parameters[Display::cursor_num].value;
            byte module_num = Display::cursor_num;
            Modules::to_config = module_num + TIME;
            delete myModules->modules[Modules::to_config];
            myModules->load_module_from_memory(index, module_num);
            if(myModules->modules[TIME + module_num]->size == 0) {
                return;
            }
            Modules::current = IO;
            Display::newPage();
        }
};

#endif

