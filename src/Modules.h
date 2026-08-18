/**
 * @file Modules.h
 * @brief Déclaration du singleton réunissant tous les modules.
 */

#ifndef MODULES_H
#define MODULES_H
#include "Module.h"
#define MODULES_SIZE 10
/** 
 * @brief  
 * 
 */

class Modules {
    public:
        static byte current;
        static unsigned int C4RefVolt;
        Module *modules[MODULES_SIZE];
        Modules();          
        void execute();
        static int getVoltage(byte pitch);
        static Module *getModule(byte num);
};

#endif
 
