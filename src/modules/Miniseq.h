/**
 * @file Miniseq.h
 * @brief Fonctions élémentaires de traitement in -> out.
 */
#ifndef MINISEQ_H
#define MINISEQ_H
#include "../Module.h"

class Miniseq: public Module {
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
        unsigned long start;
        byte noteIndex;
        byte lastPitch;

    public:
        /**
         * @brief Constructeur par défaut.
         *
         * */
        Miniseq() : Module() {
            strcpy(this->name, "MINISEQ");
            this->add({" MIDI O", 0, 0, 0, 16, 0});
            this->add({" GT OUT", 0, 0, 0, 4, 8});
            this->add({" CV OUT", 0, 0, 0, 3, 16});
            this->add({" NOTE 1", 25, 25, 0, 109, 24});
            this->add({" NOTE 2", 29, 29, 0, 109, 32});
            this->add({" NOTE 3", 32, 32, 0, 109, 40});
            this->add({" NOTE 4", 36, 36, 0, 109, 48});
            this->add({" NOTE 5", 40, 40, 0, 109, 56});
            this->setMenu();
            this->parameters[8] = {" HIDDEN", 1, 1, 1, 5, 8};
            this->noteIndex = 0;
            this->indexInList = 2;
        }
        void execute();
        void startPlay();
        void stopPlay();
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
                default:
                    if(val == 0) {
                        sprintf(temp, " NONE "); // fin de la séquence
                    } else {
                        sprintf(temp, " %.2s%d   ", 
                                notes[(val - 1) % 12], 
                                (val - 1) / 12);
                    }
                    break;
            }
            temp[7] = '\0';
        }
        void l_handlePress();
        void r_handlePress();
};

#endif



