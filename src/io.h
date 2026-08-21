/**
 * @file IO.h
 * @brief Fonctions pour la page des algos.
 */
#ifndef IO_H
#define IO_H
#include "Module.h"
#include "Modules.h"

extern Modules *myModules;
extern char *names[];

class io: public Module {
    private:
        const char *CHIO[19] = {"CLOCK", "MIDI ", "NONE ", 
            "CH 1 ", "CH 2 ", "CH 3 ", "CH 4 ", "CH 5 ", "CH 6 ", 
            "CH 7 ", "CH 8 ", "CH 9 ", "CH 10", "CH 11", "CH 12", 
            "CH 13", "CH 14", "CH 15", "CH 16"
        };
        const char *GateOut[6] = {"CLOCK ", "NONE  ",
            "DRUM 1", "DRUM 2", "GATE 1", "GATE 2"
        };
        const char *CvOut[4] = {"NONE  ",  "CV 1   ", "CV 2   ", "CV 3   "
        };

    public:
        /**
         * @brief Constructeur par défaut.
         *
         * Le bpm est compris entre 30 et 240 (Arturia keystep)
         * */
        io() : Module() {
            this->size = 0;
            this->add({" IN    ", 0, 0, 0, 18, 0});
            this->add({" CH OUT", 2, 2, 2, 18, 16});
            this->add({" CV OUT", 0, 0, 0, 3, 32});
            this->add({" GT OUT", 0, 0, 0, 5, 48});
            this->setMenu();
        }
        void getString(int val, char temp[8]) {
            switch(Display::cursor_num) {
                case 0:
                    sprintf(temp, " %.5s ", CHIO[val]);
                    break;
                case 1:
                    sprintf(temp, " %.5s ", CHIO[val]);
                    break;
                case 2:
                    sprintf(temp, " %.5s ", CvOut[val]);
                    break;
                case 3:
                    sprintf(temp, " %.6s", GateOut[val]);
                    break;
                default:
                    sprintf(temp, " %3d   ", val);
            }
            if(Modules::to_config == TIME) {
                digitalWrite(CLOCK_OUT, HIGH);
            }
            temp[7] = '\0';
        }
        void l_handlePress() {
            Modules::current = CONF;
            Display::newPage();
        }
        void r_handlePress() {
            /*
            Module *m = myModules->modules[Display::cursor_num + TIME];
            if(m->size == 0) {
                return;
            }
            Modules::current = Display::cursor_num + TIME;
            Display::newPage();
            */
        }
};

#endif

