/**
 * @file Modules.h
 * @brief Déclaration du singleton réunissant tous les modules.
 */

#ifndef MODULES_H
#define MODULES_H
#include "Module.h"

/** 
 * @brief  *
 * 
 */

class Modules {
  public:
    byte size; /**<nombre de modules */
    static byte current;
    static unsigned int c4_reference_voltage;
    Module *modules[11];
    Modules();      // do nothing but needed
    void add(Module *module);
    /** pour afficher la valeur */
    void execute();
};

#endif
 
