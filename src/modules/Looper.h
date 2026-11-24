/**
 * @class Looper
 * @brief Handle looper/sequencer.
 * 
 * Two recording modes :
 * - step by step
 * - real time 
 *
 * The max length is 64 = 4 bars 
 *
 * Record and delete with push button
 */

#ifndef LOOPER_H
#define LOOPER_H
#include "../Module.h"
#include "../memory.h"
#include "NoteStack.h"

class Looper: public Module {
    private:
        const char *ONOFF[2] = {" OFF", " ON "};
        const char *MODE[2] =  {"STbyST", "RealTi"};
        unsigned long start;
        int index;
        int stepIndex;
        byte pitchOn[6 * 16 * N_BARS];
        byte pitchOff[6 * 16 * N_BARS];
        byte velocities[6 * 16 * N_BARS];
        void startPlay(byte pitch, byte velocity);
        void stopPlay(byte pitch);
        void del_seq();
        NoteStack ns;
    public:
        Looper(byte indexInList, const char* name) : 
            Module(indexInList, name) {
            this->add(parameter{" LENGTH", 0, 0, 0, 16 * N_BARS, 0});
            this->add(parameter{" GATE  ", 1, 1, 1, 5,  8});
            this->add(parameter{" MODE  ", 1, 1, 0, 1, 16});
            this->add(parameter{" RECORD", 0, 0, 0, 1, 32});
            this->add(parameter{" DELETE", 0, 0, 0, 0, 40});
            this->add(parameter{" LOAD  ", 0, 0, 0, 25, 48});
            this->add(parameter{" SAVE  ", 0, 0, 0, 25, 56});
            this->setMenu();
            this->io[0] = parameter{" IN    ", 0, 0, 0, 16, 0};
            this->io[1] = parameter{" CH OUT", 0, 0, 0, 16, 16};
            this->io[2] = parameter{" CV OUT", 0, 0, 0, 3, 32};
            this->io[3] = parameter{" GT OUT", 0, 0, 0, 5, 48};
            this->del_seq();
            this->index = 0;
            this->stepIndex = 0;
        }
        void execute();
        void getString(int val, char temp[8]) {
            switch(Display::cursor_num) {
                case 0:
                    sprintf(temp, "  %d    ", val);
                    break;
                case 1:
                    getProgressBar(val, temp);
                    break;
                case 2:
                    sprintf(temp, " %.6s", MODE[val]);
                    this->stepIndex = 0;
                    break;
                case 4:
                    sprintf(temp, " DONE  ");
                    this->stepIndex = 0;
                    break;
                case 5:
                case 6:
                    if(val == 0) {
                        sprintf(temp, " NONE  ");
                    } else {
                        sprintf(temp, " M%d   ", val);
                    }
                    break;
                default:
                    sprintf(temp, " %.4s  ", ONOFF[val]); 
                    break;
            }
            temp[7] = '\0';
        }
        void l_handlePress();
        void r_handlePress();
        /**
         * @brief Get sequence from eeprom.
         *
         * @param m the LOOPER module
         */
        void read_sequence();
        /**
         * @brief Set sequence to eeprom.
         *
         * @param m the LOOPER module
         */
        void write_sequence();
        void handleNoteOn(byte channel, byte pitch, byte velocity);
        void handleNoteOff(byte channel, byte pitch, byte velocity);
};

#endif


