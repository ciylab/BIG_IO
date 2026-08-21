/**
 * @file Main.h
 * @brief Fonctions pour la page principale.
 */
#ifndef MAIN_H
#define MAIN_H
#include "Module.h"
#include "eeprom.h"

class Main: public Module {
    private:
        char *memory[8] = {
            "FACT",   // 0
            "SLOT A", // 1
            "SLOT B", // 2
            "SLOT C", // 3
            "SLOT D", // 4
            "SLOT E", // 5
            "SLOT F", // 6
            "SLOT G"  // 7
        };

    public:
        /**
         * @brief Constructeur par défaut.
         *
         * Le bpm est compris entre 30 et 240 (Arturia keystep)
         * */
        Main() : Module() {
            this->add({" CONFIG", 0, 0, 0, 0, 0});
            this->add({" CALIBR", 128, 128, 0, 255, 16});
            this->add({" PLAY  ", 0, 0, 0, 7, 32});
            this->add({" LOAD  ", 0, 0, 0, 7, 48});
            this->add({" SAVE  ", 1, 1, 1, 7, 56});
            this->setMenu();
        }
        void getString(int val, char temp[8]) {
            switch(Display::cursor_num) {
                case 1: // calibration
                    sprintf(temp, " %3d   ", val - 128);
                    break;
                case 3:
                    sprintf(temp, " %s ", memory[val]);
                    break;
                case 4:
                    sprintf(temp, " %s ", memory[val]);
                    break;
                default:
                    break;
            }
            temp[7] = '\0';
        }
        void r_handlePress() {
            parameter p = this->parameters[Display::cursor_num];
            if(Display::cursor_num == 3) {
                load(p.value);
                Display::print_here(" LOADED");
            } else if(Display::cursor_num == 4) {
                save(p.value);
                Display::print_here(" SAVED ");
            }
        }
};

#endif

