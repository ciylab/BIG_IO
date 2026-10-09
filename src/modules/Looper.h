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
        const char *MEM[9] = {
            "NONE  ", 
            " A    ",
            " B    ",
            " C    ",
            " D    ",
            " E    ",
            " F    ",
            " G    ",
            " H    "
        };
        unsigned long start;
        int index;
        int stepIndex;
        byte pitchOn[6 * 16 * 4]; // 384
        byte pitchOff[6 * 16 * 4]; // 384
        byte velocities[6 * 16 * 4]; // 384
        void startPlay(byte pitch, byte velocity);
        void stopPlay(byte pitch);
        void del_seq();
        byte count;
    public:
        Looper(byte indexInList, const char* name) : 
            Module(indexInList, name) {
            this->add(parameter{" LENGTH", 0, 0, 0, 64, 0});
            this->add(parameter{" MODE  ", 1, 1, 0, 1, 16});
            this->add(parameter{" RECORD", 0, 0, 0, 1, 32});
            this->add(parameter{" DELETE", 0, 0, 0, 0, 40});
            this->add(parameter{" GATE  ", 1, 1, 1, 5, 48});
            this->add(parameter{" MEMORY", 0, 0, 0, 8, 56});
            this->setMenu();
            this->io[0] = parameter{" IN    ", 0, 0, 0, 16, 0};
            this->io[1] = parameter{" CH OUT", 0, 0, 0, 16, 16};
            this->io[2] = parameter{" CV OUT", 0, 0, 0, 3, 32};
            this->io[3] = parameter{" GT OUT", 0, 0, 0, 5, 48};
            this->del_seq();
            this->index = 0;
            this->stepIndex = 0;
            this->count = 0;
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
                    getProgressBar(val, temp);
                    break;
                case 5:
                    sprintf(temp, " %.6s", MEM[val]);
                    break;
                default:
                    sprintf(temp, " %.4s  ", ONOFF[val]); 
                    break;
            }
            temp[7] = '\0';
        }
        bool getData(int index, byte data[6]);
        void setData(byte data[6]);
        void l_handlePress();
        void r_handlePress();
        void handleNoteOn(byte channel, byte pitch, byte velocity);
        void handleNoteOff(byte channel, byte pitch, byte velocity);
};

#endif


