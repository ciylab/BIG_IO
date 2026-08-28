/**
 * @class Modules
 * @brief All the modules of the project
 *
 * 4 modules on main page and config, and 8 to play 
 */

#ifndef MODULES_H
#define MODULES_H
#include "Module.h"

class Modules {
    public:
        /**
         * @brief The module of the page from 0 to 11 include MAIN...
         */
        static byte current;
        /**
         * @brief The module we work with from 4 to 11 exclude MAIN...
         *
         * When current = IO we have to_config != current.
         */
        static byte to_config;
        /**
         * Array of the 4 + 8 modules.
         */
        Module *modules[12];
        Modules();
        /**
         * To execute all the modules at each loop.
         */        
        void execute();
        /**
         * @param num the index in list of aviable modules.
         * @return the module (example TIME for 0)
         */
        static Module *getModule(byte num);
        /**
         * Load module from the list.
         * @param index in the list of aviable modules
         * @param module_num rank from 0 to 7
         */
        void load_module_from_memory(byte index, byte module_num);
};

#endif
 
