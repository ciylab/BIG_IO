/**
 * @file Time.h
 * @brief Fonctions du temps.
 */
#ifndef TIME_H
#define TIME_H
#include "Module.h"
#define DEFAULT_BPM 30


class Time: public Module {
    private:
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
        static bool newTick;

        Time() : Module() {
            this->size = 0;
            this->add({" BPM   ", DEFAULT_BPM, DEFAULT_BPM, 30, 240, 0});
            this->add({" SPEED ", 3, 3, 0, 6, 16});
            this->add({" METER ", 1, 1, 0, 2, 32});
            this->add({" RAND  ", 0, 0, 0, 5, 48});
            this->setMenu();
            this->indexInList = 0;
            this->io[0] = {" IN    ", 2, 2, 0, 2, 0};
            this->io[1] = {" CH OUT", 2, 2, 2, 18, 16};
            this->io[2] = {" CV OUT", 0, 0, 0, 0, 32};
            this->io[3] = {" GT OUT", 0, 0, 0, 1, 48};
        }
        void handleClock();
        void handleStart();
        void handleStop();
        void l_handlePress();
        void r_handlePress();
        void execute();
        void handleTick();
        void turn_led();
        void clock_send();
        void metronome(); 
        bool play_rand();       
        void getString(int val, char temp[8]) {
            switch(Display::cursor_num) {
                case 0:
                    if(this->io[0].value == 2) {
                        delta = 2500000 / val;
                    } else {
                        val = round(2500000. / delta);
                    }
                    sprintf(temp, " %3d   ", val);
                    break;
                case 1:
                    sprintf(temp, " %.2s    ", SPEED[val]);
                    break;
                case 2:
                    sprintf(temp, " %.3s   ", METER[val]);
                    break;                
                case 3:
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

