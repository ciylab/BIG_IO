/**
 * @class Looper
 * @brief Handle looper/sequencer.
 * 
 * Two recording modes
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

class Looper: public Module {
    private:
        const char *ONOFF[2] = {" OFF", " ON "};
        const char *MODE[2] =  {"STbyST", "RealTi"};
        const char *PROGRESS[6] = {
            "     ", "\'    ", "\'\'   ", "\'\'\' ", 
            "\'\'\'\' ", "\'\'\'\'\'"
        };
        unsigned long start;
        int index;
        int stepIndex;
        byte pitchOn[6 * 16 * 4]; // 384
        byte pitchOff[6 * 16 * 4]; // 384
        void startPlay(byte pitch);
        void stopPlay(byte pitch);
        void del_seq();
    public:
        Looper() : Module() {
            this->add({" LENGTH", 0, 0, 0, 64, 0});
            this->add({" MODE  ", 1, 1, 0, 1, 16});
            this->add({" RECORD", 0, 0, 0, 1, 32});
            this->add({" DELETE", 0, 0, 0, 0, 40});
            this->add({" GATE  ", 1, 1, 1, 5, 48});
            this->setMenu();
            this->indexInList = 5;
            this->io[0] = {" IN    ", 2, 2, 2, 18, 0};
            this->io[1] = {" CH OUT", 0, 0, 0, 16, 16};
            this->io[2] = {" CV OUT", 0, 0, 0, 3, 32};
            this->io[3] = {" GT OUT", 0, 0, 0, 5, 48};
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
                    sprintf(temp, " %.6s", MODE[val]);
                    this->stepIndex = 0;
                    break;
                case 3:
                    sprintf(temp, " ERASED");
                    this->stepIndex = 0;
                    break;
                case 4:
                    sprintf(temp, " %.5s ", PROGRESS[val]);
                    break;
                default:
                    sprintf(temp, " %.4s  ", ONOFF[val]); 
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


