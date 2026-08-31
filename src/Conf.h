/**
 * @class Conf
 * @brief The page to set input and output.
 */
#ifndef CONF_H
#define CONF_H

#include "Module.h"
#include "Modules.h"

/**
 * The 12 modules.
 *
 * @see BIG_IO.ino file
 */
extern Modules *myModules;

/**
 * Names of modules on screen.
 *
 * @see Module.cpp
 */
extern char *names[7];

class Conf: public Module {
    public:
        /**
         * @brief Just with numbers and data to choose module.
         */
        Conf(): Module() {
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
        /**
         * @brief To show the name of selected module.
         */
        void getString(int val, char temp[8]) {
            sprintf(temp, " %d:%.4s", 
                    Display::cursor_num + 1, 
                    names[val]);
            temp[7] = '\0';
        }
        /**
         * @brief Come back on main page.
         */
        void l_handlePress() {
            Modules::current = MAIN;
            Display::newPage();
        }
        /**
         * @brief Select module type and show io parameters.
         */
        void r_handlePress() {
            byte module_num = Display::cursor_num;
            Modules::to_config = module_num + TIME;
            byte index = this->parameters[Display::cursor_num].value;
#ifdef DEBUG            
            Serial.println("******************** PUSH");
            Serial.print("module_num : ");
            Serial.println(module_num);
            Serial.print("index : ");
            Serial.println(index);
            Serial.print("indexInList : ");
            Serial.println(
                    myModules->modules[Modules::to_config]->indexInList);
#endif            
            /**
             * If we change the current module.
             */
            if(index != 
                    myModules->modules[Modules::to_config]->indexInList) {
                // load the new module
                myModules->load_module_from_memory(index, module_num);
            }
#ifdef DEBUG  
            read_memory(module_num);
#endif            
            if(myModules->modules[Modules::to_config]->size == 0) {
                return; // Quit for NONE module.
            }
            Modules::current = IO;
            Display::newPage();
        }
};

#endif

