/**
 * @file Looper.h
 * @brief Gestion du looper.
 *
 * Le looper offre la possibilité d'enregistrer des notes et
 * de les jouer en boucle.
 */

#ifndef LOOPER_H
#define LOOPER_H
#include <MIDI.h>
#include "../Module.h"

class Looper: public Module {
    private:
        const char *ONOFF[2] = {" ON  ", " OFF "};
        unsigned long start;
        byte noteIndex;
        byte pitchs[6 * 16 * 4];
    public:
        /**
         * @brief Constructeur par défaut.
         *
         * */
        Looper() : Module() {
            this->add({" LENGTH", 0, 0, 0, 16, 0});
            this->add({" RECORD", 0, 0, 0, 1, 16});
            this->add({" DELETE", 0, 0, 0, 1, 32});
            this->setMenu();
            this->noteIndex = 0;
            this->indexInList = 6;
            this->io[0] = {" IN    ", 2, 2, 2, 2, 0};
            this->io[1] = {" CH OUT", 2, 2, 2, 18, 16};
            this->io[2] = {" CV OUT", 0, 0, 0, 3, 32};
            this->io[3] = {" GT OUT", 1, 1, 1, 5, 48};
        }
        void execute();
        void startPlay();
        void stopPlay();
        void getString(int val, char temp[8]) {
            switch(Display::cursor_num) {
                case 0:
                    sprintf(temp, "  %d    ", val);
                    break;
                default:
                    sprintf(temp, " %.3s   ", ONOFF[val]); 
                    break;
            }
            temp[7] = '\0';
        }
        void l_handlePress();
        void r_handlePress();
        void handleNoteOn(byte channel, byte pitch, byte velocity);
        void handleNoteOff(byte channel, byte pitch, byte velocity);
};

#endif



