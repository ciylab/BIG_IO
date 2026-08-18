/**
 * @file Trigger.h
 * @brief Fonctions de déclenchement de gates.
 */
#ifndef TRIGGER_H
#define TRIGGER_H
#include "../Module.h"


class Trigger: public Module {
    private:
        const char *InOut[22] = {"NONE  ", "CLOCK ",
            "DRUM 1", "DRUM 2", "GATE 1", "GATE 2",
            "CH 1  ", "CH 2  ", "CH 3  ", "CH 4  ", "CH 5  ", "CH 6  ", 
            "CH 7  ", "CH 8  ", "CH 9  ", "CH 10 ", "CH 11 ", "CH 12 ", 
            "CH 13 ", "CH 14 ", "CH 15 ", "CH 16 "
        };
        const char *notes[12] = {
            " C", "C#", " D", "D#", " E", " F", 
            "F#", " G", "G#", " A", "A#", " B"
        };
        const char *PROGRESS[6] = {
            "     ", "|    ", "||   ", "||| ", "|||| ", "|||||"
        };

        byte lastPitch;
    public:
        unsigned long start;
        /**
         * @brief Constructeur par défaut.
         *
         */
        Trigger() : Module() {
            strcpy(this->name, "TRIGGER");
            this->add({" OUT   ", 0, 0, 0, 21, 0});
            this->add({" LENGTH", 16, 16, 0, 16, 8});
            this->add({" BEATS ", 4, 4, 0, 16, 16});
            this->add({" SHIFT ", 0, 0, 0, 16, 24});
            this->add({" PITCH ", 48, 48, 21, 108, 32});
            this->add({" GATE  ", 1, 1, 1, 5, 40});
            this->add({" beats ", 0, 0, 0, 16, 48});
            this->add({" shift ", 0, 0, 0, 16, 56});
            this->setMenu();
            this->indexInList = 5;
            this->parameters[8] = {" HIDDEN", 1, 1, 1, 5, 0};
        }
        void execute();
        void getString(int val, char temp[8]) {
            switch(Display::cursor_num) {
                case 0:
                    if(!hidden) {
                        sprintf(temp, " %.5s ", PROGRESS[val]);
                    } else {
                        sprintf(temp, " %.6s", InOut[val]);
                    }
                    break;
                case 4:
                    sprintf(temp, " %.2s%d   ", notes[val % 12], val / 12);
                    break;
                default:
                    sprintf(temp, " %2d   ", val);
                    break;
            }
            temp[7] = '\0';
        }
        bool isPulse();
        void startPlay();
        void stopPlay();
        void l_handlePress();
        void r_handlePress();
};

#endif

