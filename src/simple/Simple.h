/**
 * @file Simple.h
 * @brief Fonctions élémentaires de traitement in -> out.
 */
#ifndef SIMPLE_H
#define SIMPLE_H
#include "../base/Module.h"


class Simple: public Module {
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
        byte pitch_send[128];
    public:
        /**
         * @brief Constructeur par défaut.
         *
         * */
        Simple(char name[8]) : Module(name) {
            this->add({" MIDI I", 1, 1, 0, 16, 0});
            this->add({" MIDI O", 2, 2, 0, 16, 8});
            this->add({" GT OUT", 3, 3, 0, 4, 16});
            this->add({" CV OUT", 1, 1, 0, 3, 24});
            this->add({" MIN   ", 0, 0, 21, 108, 32});
            this->add({" MAX   ", 108, 108, 21, 108, 40});
            this->add({" TRANSP", 0, 0, 0, 11, 48});
            this->setMenu();
            for (int i = 0; i < 128; i++) {
                pitch_send[i] = 0;
            }
        }
        bool isInRange(byte pitch);
        void handleNoteOn(byte channel, byte pitch, byte velocity);
        void handleNoteOff(byte channel, byte pitch, byte velocity);
        void getString(int val, char temp[8]) {
            switch(Display::cursor_num) {
                case 0:
                    sprintf(temp, " %.6s", MIDIio[val]);
                    break;
                case 1:
                    sprintf(temp, " %.6s", MIDIio[val]);
                    break;
                case 2:
                    sprintf(temp, " %.6s", GateOut[val]);
                    break;
                case 3:
                    sprintf(temp, " %.6s", CvOut[val]);
                    break;
                case 4:
                    sprintf(temp, " %.2s%d   ", notes[val % 12], val / 12);
                    break;
                case 5:
                    sprintf(temp, " %.2s%d   ", notes[val % 12], val / 12);
                    break;
                case 6:
                    sprintf(temp, " %.2s    ", notes[val % 12]);
                    break;
                default:
                    sprintf(temp, " %2d   ", val);
                    break;
            }
            temp[7] = '\0';
        }
        void r_handlePress();
};

#endif


