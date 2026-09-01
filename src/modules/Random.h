/**
 * @class Random
 * @brief Random pitch generator
 *
 * We can choose scale and key
 * Freeze possibility
 * human parameter to set some melodic variation
 */
#ifndef RANDOM_H
#define RANDOM_H
#include "../Module.h"

/**
 * @brief memory size for 4 bars 
 */

#define R_SEQ_SIZE 64 

#define NUM_SCALE 4 

class Random: public Module {
    private:
        const char *SCALES[NUM_SCALE] = {"CHROMA", "MAJOR ", 
            "PENTA ", "HARMON"};
        const char *ONOFF[2] = {"OFF", "ON "};
        static int scale_size[NUM_SCALE];
        // number of pitch lower than the one
        static byte count[NUM_SCALE][12];  
        static byte pitchs[NUM_SCALE][12]; // i-th pitch in C
        static byte scales[NUM_SCALE][12];
        static int shift[5];
        byte sequence[R_SEQ_SIZE];
        byte lastPitch;
        void startPlay();
        void stopPlay(byte pitch);
        static byte get_count(byte scale, byte note);
        static byte get_pitch(byte scale, byte rank);
        static byte rand_note(byte min, byte max, byte tone, byte scale);
        byte getRandomNote();
        bool isInRange(byte pitch);
        unsigned long start;
        byte current_index;
    public:
        Random() : Module() {
            this->add({" LENGTH", 0, 0, 0, 16, 0});
            this->add({" GATE  ", 1, 1, 1, 5, 8});
            this->add({" SCALE ", 0, 0, 0, 3, 16});
            this->add({" KEY   ", 0, 0, 0, 11, 24});
            this->add({" FREEZE", 0, 0, 0, 1, 32});
            this->add({" HUMAN ", 0, 0, 0, 5, 40});
            this->add({" MIN   ", 24, 24, 0, 108, 48});
            this->add({" MAX   ", 72, 72, 0, 108, 56});
            this->setMenu();
            this->indexInList = 2;
            this->io[0] = {" IN    ", 0, 0, 0, 0, 0};
            this->io[1] = {" CH OUT", 0, 0, 0, 16, 16};
            this->io[2] = {" CV OUT", 0, 0, 0, 3, 32};
            this->io[3] = {" GT OUT", 0, 0, 0, 5, 48};
            for(int i = 0; i < R_SEQ_SIZE; i++) {
                this->sequence[i] = 0;
            }
        }
        void execute();
        void getString(int val, char temp[8]) {
            switch(Display::cursor_num) {
                case 0:
                    sprintf(temp, " %2d    ", val);
                    break;
                case 1:
                    sprintf(temp, " %s", PROGRESS[val]);
                    break;
                case 2:
                    sprintf(temp, " %.6s", SCALES[val]);
                    break;
                case 3:
                    sprintf(temp, " %.2s    ", NOTES[val]);
                    break;
                case 4:
                    sprintf(temp, " %.3s   ", ONOFF[val]);
                    break;                
                case 5:
                    sprintf(temp, " %s", PROGRESS[val]);
                    break; 
                default:
                    sprintf(temp, " %.2s%d  ", 
                            NOTES[val % 12], val / 12);
                    break;
            }
            temp[7] = '\0';
        }
        void l_handlePress();
        void r_handlePress();
};

#endif


