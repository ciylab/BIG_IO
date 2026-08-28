/**
 * @class Time
 * @brief Functions to handle time.
 * 
 * The time is divided in 24 ticks (PPQN). 
 * The Time module generate a new tick from the bpm.
 * and then each module execute something accordingly.
 *
 * The bpm is and integer between 30 and 240 (Arturia keystep).
 *
 * There is always a midi clock signal out.
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
            "     ", "\'    ", "\'\'   ", "\'\'\' ", 
            "\'\'\'\' ", "\'\'\'\'\'"
        };
        /**
         * @brief Diff between two ticks in microseconds.
         */
        unsigned long delta;
        /**
         * @brief The time when the last tick.
         */
        unsigned long lastTime;

        unsigned long lastClockIn;
        /**
         * @brief Used to listen **clock in** pulse, 
         */
        bool start;
        /**
         * @brief Init values to handle clock.
         */
        void init();
        /**
         * @brief Generate a new tick and handle this event.
         */
        void handleTick();
        /**
         * @brief Open/close gate **clock out**.
         */
        void handleGate();
        /**
         * @brief Send midi clock and call handleTick.
         */
        void clockSend();        
        /**
         * @brief Send note on midi channel.
         */
        void metronome();
        /**
         * @brief Chaos clock out.
         */ 
        bool playRand();
        /**
         * @brief True if a **clock in** is detected.
         */
        bool listen_clock_pulse();
 
   public:
        /**
         * @brief The tick number.
         */
        static unsigned long tick;
        /**
         * @brief While the tick is not executed 
         */
        static bool newTick;
                
        Time() : Module() {
            this->size = 0;
            this->add({" BPM   ", DEFAULT_BPM, DEFAULT_BPM, 30, 240, 0});
            this->add({" SPEED ", 3, 3, 0, 6, 16});
            this->add({" METER ", 1, 1, 0, 2, 32});
            this->add({" CHAOS ", 0, 0, 0, 5, 48});
            this->setMenu();
            this->indexInList = 0;
            this->io[0] = {" IN    ", 0, 0, 0, 2, 0};
            this->io[1] = {" CH OUT", 1, 1, 0, 16, 16};
            this->io[2] = {" CV OUT", 0, 0, 0, 0, 32};
            this->io[3] = {" GT OUT", 0, 0, 0, 1, 48};
            this->init();
        }
        /**
         * @brief When clock is midi in.
         */
        void handleClock();
        void handleStart();
        void handleStop();
        /**
         * @brief Clear and stop any metronome note.
         */
        void panic();
        void l_handlePress();
        void r_handlePress();
        /**
         * @brief At each loop.
         *
         * Call clockSend in case of no **midi in**.
         */
        void execute();
        void getString(int val, char temp[8]) {
            switch(Display::cursor_num) {
                case 0:
                    if(this->io[0].value == 0) {
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

//bool listen_clock_pulse();
#endif

