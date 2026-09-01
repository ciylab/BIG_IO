/**
 * @class Module
 * @brief Base class of the project to handle events.
 */

#ifndef MODULE_H
#define MODULE_H
#include "Display.h"
#include "midi.h"
#include "gate.h"

#define MAIN 0
#define CONF 1
#define IO   2
#define PLAY 3
#define TIME 4

/**
 * @struct parameter
 * @brief For any parameter of the project.
 * 
 * Value changes by right encoder. Buffer can be used when
 * value change during note off for example. 
 * Its id is **cursor_num**.
 */
struct parameter {
    char name[8];    //!<  name to display
    byte value;      //!<  uses when playing
    byte buffer;     //!<  value sometime used to prevent bug on change
    byte min;        //!<  min value often 0
    byte max;        //!<  max value
    byte cursor_pos; //!<  on screen from 0 to 63
};

class Module {
    public:
        static const char *NOTES[12];
        parameter io[4]; //!< Array of input/output parameters.
        parameter parameters[8]; //!< Array of data to play.
        /**
         * @brief temporary parameter value : no direct change only when 
         * pushing
         */
        byte temp;
        int size;
        char name[8]; //!< Name on the screen.
        char text[64]; //!< Page text.
        bool new_value; //!< Flag to only show value before change.
        byte indexInList; //!< Num of modules in base list.
        Module();
        virtual ~Module() {}
        /**
         * @brief Add a new parameter. 
         *
         * @param p parameter format {"", , , , , }
         */
        void add(parameter p);
        /**
         * @brief Set the text page.
         */
        virtual void setMenu();
        /**
         * @brief Specific midi function.
         */
        virtual void handleNoteOn(
                byte channel, byte pitch, byte velocity) {} 
        /**
         * @brief Specific midi function.
         */
        virtual void handleNoteOff(
                byte channel, byte pitch, byte velocity) {}
        /**
         * @brief Specific midi function.
         */
        virtual void handleClock() {}
        /**
         * @brief Specific midi function.
         */
        virtual void handleStart() {}
        /**
         * @brief Specific midi function.
         */
        virtual void handleStop() {}
        /**
         * @brief Classic midi panic function.
         */
        void panic() {
            if(this->io[1].value != 0) {
                clear_channel(this->io[1].value);
                this->io[1].value = 0;
            }
        }
        /**
         * @brief Close gate.
         */
        void closeGate() {
            byte gate = this->io[3].value;
            if(gate != 0) {
                digitalWrite(gates[gate - 1], HIGH);
            }
            this->io[3].value = 0;
        }
        /**
         * @brief Specific handle encoder event.
         */
        virtual void l_handlePress();
        /**
         * @brief Specific handle encoder event.
         */
        virtual void r_handlePress();
        /**
         * @brief Put string for val in temp.
         * 
         * It depends on string, int, note...
         * @param val parameter value
         * @param temp string to show       
         * @remark Depends on Display::cursor_num 
         */
        virtual void getString(int val, char temp[8]) {}
        /**
         * @brief Show progress bar.
         */
        void getProgressBar(int val, char temp[8]) {
            temp[0] = ' ';
            for (int i = 1; i <= val; i++) {
                temp[i] = 134;
            }
            for (int i = val + 1; i <= 6; i++) {
                temp[i] = ' ';
            }
            temp[7] = '\0';
        }
        /**
         * @brief Each BluePill loop execute all modules.
         */ 
        virtual void execute() {}
        /**
         * @brief General function to send midi note
         */
        virtual void startPlayMIDI(byte pitch);
        /**
         * @brief General function to send cv
         */
        virtual void startPlayCV(byte pitch);
        /**
         * @brief General function to send gate
         */
        virtual void startPlayGate(); 
        /**
         * @brief General function to send midi note
         */
        virtual void stopPlayMIDI(byte pitch);
        /**
         * @brief General function to send cv
         */
        virtual void stopPlayCV();
        /**
         * @brief General function to send gate
         */
        virtual void stopPlayGate(); 
        /**
         * @brief free memory
         */
        static void del(Module *m) {
            if(m != NULL) {
                delete m;
                m = NULL;
            }
        }
};

#endif

