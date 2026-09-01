/**
 * @class Simple
 * @brief simple in -> out 
 *
 * to send for example midi channel onto cv/gate
 * we can choose range and apply transposition
 */
#ifndef SIMPLE_H
#define SIMPLE_H
#include "../Module.h"


class Simple: public Module {
    private:
        byte pitch_send[128];
        bool isInRange(byte pitch);
    public:
        Simple(): Module() {
            this->add({" MIN   ", 0, 0, 0, 108, 0});
            this->add({" MAX   ", 108, 108, 0, 108, 16});
            this->add({" TRANSP", 0, 0, 0, 11, 32});
            this->setMenu();
            this->indexInList = 3;
            this->io[0] = {" IN    ", 0, 0, 0, 16, 0};
            this->io[1] = {" CH OUT", 0, 0, 0, 16, 16};
            this->io[2] = {" CV OUT", 0, 0, 0, 3, 32};
            this->io[3] = {" GT OUT", 0, 0, 0, 5, 48};
        }
        void handleNoteOn(byte channel, byte pitch, byte velocity);
        void handleNoteOff(byte channel, byte pitch, byte velocity);
        void getString(int val, char temp[8]) {
            switch(Display::cursor_num) {
                case 0:
                    sprintf(temp, " %.2s%d   ", NOTES[val % 12], val / 12);
                    break;
                case 1:
                    sprintf(temp, " %.2s%d   ", NOTES[val % 12], val / 12);
                    break;
                case 2:
                    sprintf(temp, " %.2s    ", NOTES[val % 12]);
                    break;
                default:
                    sprintf(temp, " %2d   ", val);
                    break;
            }
            temp[7] = '\0';
        }
        void r_handlePress();
        void l_handlePress();        
};

#endif


