/**
 * @file Trigger.h
 * @brief Dual euclidian generator 
 */
#ifndef TRIGGER_H
#define TRIGGER_H
#include "../Module.h"


class Trigger: public Module {
    private:
        const char *notes[12] = {
            " C", "C#", " D", "D#", " E", " F", 
            "F#", " G", "G#", " A", "A#", " B"
        };
        const char *PROGRESS[6] = {
            "     ", "\'    ", "\'\'   ", "\'\'\' ", 
            "\'\'\'\' ", "\'\'\'\'\'"
        }; 
        /**
         * @brief if true then we play
         */       
        bool isPulse();
        void startPlay(byte pitch);
        void stopPlay(byte pitch);
        /**
         * @brief to handle gate off
         */
        unsigned long start;
    public:
        Trigger() : Module() {
            this->add({" LENGTH", 16, 16, 0, 16, 0});
            this->add({" GATE  ", 1, 1, 1, 5, 8});
            this->add({" BEATS ", 4, 4, 0, 16, 16});
            this->add({" SHIFT ", 0, 0, 0, 16, 24});
            this->add({" beats ", 0, 0, 0, 16, 32});
            this->add({" shift ", 0, 0, 0, 16, 40});
            this->add({" PITCH ", 48, 48, 21, 108, 48});
            this->setMenu();
            this->indexInList = 4;
            this->io[0] = {" IN    ", 0, 0, 0, 0, 0};
            this->io[1] = {" CH OUT", 0, 0, 0, 16, 16};
            this->io[2] = {" CV OUT", 0, 0, 0, 3, 32};
            this->io[3] = {" GT OUT", 0, 0, 0, 5, 48};
        }
        void execute();
        void getString(int val, char temp[8]) {
            switch(Display::cursor_num) {
                case 1:
                    sprintf(temp, " %.5s ", PROGRESS[val]);
                    break;
                case 6:
                    sprintf(temp, " %.2s%d   ", notes[val % 12], val / 12);
                    break;
                case 7:
                    sprintf(temp, " %.2s%d   ", notes[val % 12], val / 12);
                    break;
                default:
                    sprintf(temp, " %2d    ", val);
                    break;
            }
            temp[7] = '\0';
        }
        void l_handlePress();
        void r_handlePress();
};

#endif

