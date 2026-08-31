/**
 * @file Main.h
 * @brief Functions and parameters for the Main page.
 * 
 * 1. CONFIG : input/output
 * 2. CALIB : the default value is 3276 (= 5 * 4095 / 4)
 * and it is possible to adjust form -128 to + 127.
 * 3. PLAY : to change values in real time
 * 4. LOAD : a preset of 8 modules. Fact can't be saved.
 * 5. SAVE : choose slot for current conf.
 */
#ifndef MAIN_H
#define MAIN_H
#include "Module.h"
/**
 * @brief For load/save.
 */
#include "eeprom.h"

class Main: public Module {
    private:
        const char *memory[8] = {
            "FACT  ", // 0
            "SLOT A", // 1
            "SLOT B", // 2
            "SLOT C", // 3
            "SLOT D", // 4
            "SLOT E", // 5
            "SLOT F", // 6
            "SLOT G"  // 7
        };

    public:
        Main() : Module() {
            this->add({" CONFIG", 0, 0, 0, 0, 0});
            this->add({" PLAY  ", 0, 0, 0, 7, 16});
            this->add({" LOAD  ", 0, 0, 0, 7, 32});
            this->add({" SAVE  ", 1, 1, 1, 7, 40});
            this->add({" CALIBR", 0, 0, 0, 0, 48});
            this->setMenu();
        }
        void getString(int val, char temp[8]) {
            switch(Display::cursor_num) {
                case 2:
                    sprintf(temp, " %s ", memory[val]);
                    break;
                case 3:
                    sprintf(temp, " %s ", memory[val]);
                    break;
                default:
                    break;
            }
            temp[7] = '\0';
        }
        void r_handlePress() {
            parameter *p = &(this->parameters)[Display::cursor_num];
            if(this->new_value && Display::cursor_num == 2) {
                p->value = this->temp;
                load(p->value);
                Display::print_here(" LOADED");
            } else if(this->new_value && Display::cursor_num == 3) {
                // p->value = this->temp;
                // save(p->value);
                Display::print_here(" SAVED ");
            }
        }
};

#endif

