/**
 * @file Time.h
 * @brief Fonctions du temps.
 */
#ifndef TIME_H
#define TIME_H
#include "../base/Module.h"


class Time: public Module {
    private:
        const char *InOut[19] = {"NONE ", "CLOCK", "MIDI ",
            "CH 1 ", "CH 2 ", "CH 3 ", "CH 4 ", "CH 5 ", "CH 6 ", 
            "CH 7 ", "CH 8 ", "CH 9 ", "CH 10", "CH 11", "CH 12", 
            "CH 13", "CH 14", "CH 15", "CH 16"
        };
        const char *SPEED[7] = {"/4", "/3", "/2", "x1", "x2", "x3", "x4"};
        const char *METER[3] = {"3/4", "4/4", "5/4"};
        const char *PROGRESS[6] = {
            "     ", "|    ", "||   ", "||| ", "|||| ", "|||||"
        };
   public:
        /**
         * @brief Constructeur par défaut.
         *
         * Le bpm est compris entre 30 et 240 (Arturia keystep)
         * */
        static unsigned long tick;
        static unsigned long delta;
        static unsigned long lastTime;
        static unsigned long lastClockIn;
        Time(char name[8]) : Module(name) {
            this->add({" IN    ", 2, 2, 0, 2, 0});
            this->add({" OUT   ", 1, 1, 0, 18, 8});
            this->add({" BPM   ", 120, 120, 30, 240, 16});
            this->add({" SPEED ", 3, 3, 0, 6, 24});
            this->add({" METER ", 1, 1, 0, 2, 32});
            this->add({" RAND  ", 0, 0, 0, 5, 40});
            this->setMenu();
        }
        void handleClock();
        void handleStart();
        void handleStop();
        void execute();
        void handleTick();
        void turn_led();
        void clock_send();
        void metronome(); 
        bool play_rand();       
        void getString(int val, char temp[8]) {
            switch(Display::cursor_num) {
                case 0:
                    if (val == 0) {
                        delta = 2500000 / this->parameters[2].value;
                    }
                    sprintf(temp, " %.5s ", InOut[val]);
                    digitalWrite(CLOCK_OUT, HIGH);
                    break;
                case 1:
                    sprintf(temp, " %.5s ", InOut[val]);
                    digitalWrite(CLOCK_OUT, HIGH);
                    break;
                case 2:
                    if(this->parameters[0].value == 0) {
                        delta = 2500000 / val;
                    } else if(this->parameters[0].value == 1) {
                        val = round(2500000. / delta);
                    }
                    sprintf(temp, " %3d   ", val);
                    break;
                case 3:
                    sprintf(temp, " %.2s    ", SPEED[val]);
                    break;
                case 4:
                    sprintf(temp, " %.3s   ", METER[val]);
                    break;                
                case 5:
                    sprintf(temp, " %.5s ", PROGRESS[val]);
                    break;
               default:
                    break;
            }
            temp[7] = '\0';
        }
};

bool listen_clock_pulse();

#endif

