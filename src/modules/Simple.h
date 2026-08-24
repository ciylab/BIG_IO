/**
 * @file Simple.h
 * @brief Fonctions élémentaires de traitement in -> out.
 */
#ifndef SIMPLE_H
#define SIMPLE_H
#include "../Module.h"


class Simple: public Module {
    private:
        const char *notes[12] = {
            " C", "C#", " D", "D#", " E", " F", 
            "F#", " G", "G#", " A", "A#", " B"
        };
        byte pitch_send[128];
    public:
        /**
         * @brief Constructeur par défaut.
         *
         * */
        Simple(): Module() {
            this->add({" MIN   ", 0, 0, 0, 108, 0});
            this->add({" MAX   ", 108, 108, 0, 108, 16});
            this->add({" TRANSP", 0, 0, 0, 11, 32});
            this->setMenu();
            this->indexInList = 3;
            for (int i = 0; i < 128; i++) {
                pitch_send[i] = 0;
            }
            this->io[0] = {" IN    ", 2, 2, 2, 18, 0};
            this->io[1] = {" CH OUT", 2, 2, 2, 18, 16};
            this->io[2] = {" CV OUT", 0, 0, 0, 3, 32};
            this->io[3] = {" GT OUT", 1, 1, 1, 5, 48};
        }
        bool isInRange(byte pitch);
        void handleNoteOn(byte channel, byte pitch, byte velocity);
        void handleNoteOff(byte channel, byte pitch, byte velocity);
        void getString(int val, char temp[8]) {
            switch(Display::cursor_num) {
                case 0:
                    sprintf(temp, " %.2s%d   ", notes[val % 12], val / 12);
                    break;
                case 1:
                    sprintf(temp, " %.2s%d   ", notes[val % 12], val / 12);
                    break;
                case 2:
                    sprintf(temp, " %.2s    ", notes[val % 12]);
                    break;
                default:
                    sprintf(temp, " %2d   ", val);
                    break;
            }
            temp[7] = '\0';
        }
        void r_handlePress();
        void l_handlePress();        
        void panic();
};

#endif


