/**
 * @file Time.h
 * @brief Fonctions du temps.
 */
#ifndef TIME_H
#define TIME_H
#include "../base/Module.h"


class Time: public Module {
    private:
        const char *In[3]  = {"NONE", "MIDI", "TRIG"};
        const char *SPEED[7] = {"/4", "/3", "/2", "x1", "x2", "x3", "x4"};
        const char *METER[3] = {"3/4", "4/4", "5/4"};
        const char *ONOFF[2] = {"OFF", "ON "};
    public:
        /**
         * @brief Constructeur par défaut.
         *
         * Le bpm est compris entre 30 et 240 (Arturia keystep)
         * */
        Time(char name[8]) : Module(name) {
            static unsigned long tick = 0;
            this->add({" IN    ", 0, 0, 0, 2, 0});
            this->add({" OUT   ", 0, 0, 0, 22, 8});
            this->add({" BPM   ", 60, 60, 30, 240, 16});
            this->add({" SPEED ", 3, 3, 0, 6, 24});
            this->add({" METER ", 1, 1, 0, 2, 32});
            this->add({" METRON", 0, 0, 0, 1, 40});
            this->setMenu();
        }
        void handleNoteOn(byte channel, byte pitch, byte velocity) {}
        void handleNoteOff(byte channel, byte pitch, byte velocity) {}
        void handleClock() override;
        void getString(int val, char temp[8]) {
            switch(Display::cursor_num) {
                case 0:
                    sprintf(temp, " %.4s  ", In[val]);
                    break;
                case 1:
                    sprintf(temp, " %.4s  ", In[val]);
                    break;
                case 2:
                    sprintf(temp, " %3d   ", val);
                    break;
                case 3:
                    sprintf(temp, " %.2s    ", SPEED[val]);
                    break;
                case 4:
                    sprintf(temp, " %.3s   ", METER[val]);
                    break;
                case 5:
                    sprintf(temp, " %.3s   ", ONOFF[val]);
                    break;
                default:
                    break;
            }
            temp[7] = '\0';
        }
};

#endif

