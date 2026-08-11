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
    Module *modules[11];
    Modules();      // do nothing but needed
    void add(Module *module);
    /** pour afficher la valeur */
    void execute();
};

#endif
 
