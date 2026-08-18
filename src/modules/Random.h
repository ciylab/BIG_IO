/**
 * @file Random.h
 * @brief Fonctions de génération aléatoire.
 */
#ifndef RANDOM_H
#define RANDOM_H
#include "../Module.h"

/**
 * taille de la mémoire pour enregistrer 4 mesures de 16 double-croches 
 */

#define R_SEQ_SIZE 64 

#define NUM_SCALE 4 /**<nombre de gammes */

class Random: public Module {
    private:
        const char *MIDIio[17] = {"NONE  ",
            "CH 1  ", "CH 2  ", "CH 3  ", "CH 4  ", "CH 5  ", "CH 6  ", 
            "CH 7  ", "CH 8  ", "CH 9  ", "CH 10 ", "CH 11 ", "CH 12 ", 
            "CH 13 ", "CH 14 ", "CH 15 ", "CH 16 "
        };
        const char *GateOut[5] = {"NONE  ",
            "DRUM 1", "DRUM 2", "GATE 1", "GATE 2"
        };
        const char *CvOut[4] = {"NONE  ",  "CV 1  ", "CV 2  ", "CV 3  "
        };

        const char *notes[12] = {
            " C", "C#", " D", "D#", " E", " F", 
            "F#", " G", "G#", " A", "A#", " B"
        };
        const char *PROGRESS[6] = {
            "     ", "|    ", "||   ", "||| ", "|||| ", "|||||"
        };
        const char *SCALES[NUM_SCALE] = {"CHROMA", "MAJOR ", 
            "PENTA ", "HARMON"};
        const char *ONOFF[2] = {"OFF", "ON "};
        static int scale_size[NUM_SCALE];
        // number of pitch lower than the one
        static byte count[NUM_SCALE][12];  
        static byte pitchs[NUM_SCALE][12]; // i-th pitch in C
        static byte scales[NUM_SCALE][12];
        byte sequence[R_SEQ_SIZE];
        byte lastPitch;
        byte min;
        byte max;
        bool showMax;
    public:
        unsigned long start;
        byte current_index;
        /**
         * @brief Constructeur par défaut.
         *
         */
        Random() : Module() { 
            strcpy(this->name, "RANDOM");           
            this->add({" MIDI O", 2, 2, 0, 16, 0});
            this->add({" GT OUT", 3, 3, 0, 4, 8});
            this->add({" CV OUT", 1, 1, 0, 3, 16});
            this->add({" LENGTH", 1, 1, 0, 16, 24});
            this->add({" SCALE ", 0, 0, 0, 3, 32});
            this->add({" KEY   ", 0, 0, 0, 11, 40});
            this->add({" FREEZE", 0, 0, 0, 1, 48});
            this->add({" RANGE ", 108, 108, 0, 216, 56});
            this->setMenu();
            this->parameters[8] = {" HIDDEN", 1, 1, 1, 5, 0};
            this->indexInList = 3;
            this->min = 24;
            this->max = 72;
            this->showMax = true;
            for(int i = 0; i < R_SEQ_SIZE; i++) {
                this->sequence[i] = 0;
            }
        }
        static byte get_count(byte scale, byte note);
        static byte get_pitch(byte scale, byte rank);
        static byte rand_note(byte min, byte max, byte tone, byte scale);
        byte getRandomNote();
        bool isInRange(byte pitch);
        void startPlay();
        void stopPlay();
        void execute();
        void getString(int val, char temp[8]) {
            switch(Display::cursor_num) {
                case 0:
                    sprintf(temp, " %.6s", MIDIio[val]);
                    break;
                case 1:
                    if(!hidden) {
                        sprintf(temp, " %.5s ", PROGRESS[val]);
                    } else {
                        sprintf(temp, " %.6s", GateOut[val]);
                    }
                    break;
                case 2:
                    sprintf(temp, " %.6s", CvOut[val]);
                    break;
                case 3:
                    sprintf(temp, " %2d   ", val);
                    break;
                case 4:
                    sprintf(temp, " %.6s", SCALES[val]);
                    break;
                case 5:
                    sprintf(temp, " %.2s    ", notes[val]);
                    break;
                case 6:
                    sprintf(temp, " %.3s  ", ONOFF[val]);
                    break;                
                case 7:
                    if(val < 108) {
                        max = val;
                        sprintf(temp, " MX %.2s%d", 
                                notes[val % 12], val / 12);
                    } else if (108 < val) {
                        val = val - 108;
                        min = val;
                        sprintf(temp, " MN %.2s%d", 
                                notes[val % 12], val / 12);
                    } else {
                        sprintf(temp, " ALL  ");
                    }
                    break;

            }
            temp[7] = '\0';
        }
        void l_handlePress();
        void r_handlePress();
};

#endif


