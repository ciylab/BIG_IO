/**
 * @file Miniseq.h
 * @brief Fonctions élémentaires de traitement in -> out.
 */
#ifndef MINISEQ_H
#define MINISEQ_H
#include "../Module.h"

class Miniseq: public Module {
    private:
        const char *notes[12] = {
            " C", "C#", " D", "D#", " E", " F", 
            "F#", " G", "G#", " A", "A#", " B"
        };
        const char *PROGRESS[6] = {
            "     ", "|    ", "||   ", "||| ", "|||| ", "|||||"
        };
        unsigned long start;
        byte noteIndex;
    public:
        /**
         * @brief Constructeur par défaut.
         *
         * */
        Miniseq() : Module() {
            this->add({" LENGTH", 0, 0, 0, 6, 0});
            this->add({" GATE  ", 1, 1, 1, 5, 8});
            this->add({" NOTE 1", 24, 24, 0, 109, 16});
            this->add({" NOTE 2", 28, 28, 0, 109, 24});
            this->add({" NOTE 3", 31, 31, 0, 109, 32});
            this->add({" NOTE 4", 35, 35, 0, 109, 40});
            this->add({" NOTE 5", 38, 38, 0, 109, 48});
            this->add({" NOTE 6", 41, 41, 0, 109, 56});
            this->setMenu();
            this->noteIndex = 0;
            this->indexInList = 1;
            this->io[0] = {" IN    ", 2, 2, 2, 2, 0};
            this->io[1] = {" CH OUT", 2, 2, 2, 18, 16};
            this->io[2] = {" CV OUT", 0, 0, 0, 3, 32};
            this->io[3] = {" GT OUT", 1, 1, 1, 5, 48};
        }
        void execute();
        void startPlay();
        void stopPlay();
        void getString(int val, char temp[8]) {
            switch(Display::cursor_num) {
                case 0:
                    sprintf(temp, "  %d    ", val);
                    break;
                case 1:
                    sprintf(temp, " %s ", PROGRESS[val]);
                    break;
                default:
                    sprintf(temp, " %.2s%d   ", 
                            notes[val % 12], val / 12);
                    break;
            }
            temp[7] = '\0';
        }
        void l_handlePress();
        void r_handlePress();
};

#endif



