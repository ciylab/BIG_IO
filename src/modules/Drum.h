/**
 * @class Drum
 * @brief Dual euclidian generator 
 */
#ifndef TRIGGER_H
#define TRIGGER_H
#include "../Module.h"


class Drum: public Module {
    private:
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
        Drum(byte indexInList, const char* name) : 
            Module(indexInList, name) {
            this->add(parameter{" LENGTH", 16, 16, 0, 16, 0});
            this->add(parameter{" GATE  ", 1, 1, 1, 5, 8});
            this->add(parameter{" BEATS ", 4, 4, 0, 16, 16});
            this->add(parameter{" SHIFT ", 0, 0, 0, 16, 24});
            this->add(parameter{" beats ", 0, 0, 0, 16, 32});
            this->add(parameter{" shift ", 0, 0, 0, 16, 40});
            this->add(parameter{" PITCH ", 48, 48, 21, 108, 48});
            this->setMenu();
            this->io[0] = parameter{" IN    ", 0, 0, 0, 16, 0};
            this->io[1] = parameter{" CH OUT", 0, 0, 0, 16, 16};
            this->io[2] = parameter{" CV OUT", 0, 0, 0, 0, 32};
            this->io[3] = parameter{" GT OUT", 0, 0, 0, 5, 48};
        }
        void execute();
        void getString(int val, char temp[8]) {
            switch(Display::cursor_num) {
                case 1:
                    getProgressBar(val, temp);
                    break;
                case 6:
                    sprintf(temp, " %.2s%d   ", NOTES[val % 12], val / 12);
                    break;
                case 7:
                    sprintf(temp, " %.2s%d   ", NOTES[val % 12], val / 12);
                    break;
                default:
                    sprintf(temp, " %2d    ", val);
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

