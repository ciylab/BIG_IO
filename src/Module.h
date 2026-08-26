/**
 * @class Module.
 * @brief Déclaration de la classe.
 * @details Classe de base déclarant les variables et méthodes communes.
 */

#ifndef MODULE_H
#define MODULE_H
#include "config.h"
#include "Display.h"
#include "midi.h"

class Module {
    public:
        parameter io[4]; //!<Tableau des paramètres input/output.
        parameter parameters[8]; //!<Tableau des paramètres de jeu.
        int size; //!<Nombre de paramètres pour ce module.
        char name[8]; //!<Nom du module qui figure sur l'écran.
        char text[TEXT_SIZE]; //!<Texte des paramètres du module.
        bool new_value; //!<Indique qu'on affiche avant modification.
        byte indexInList; //!<Rang dans la liste des modules pour l'import
        Module(); 
        /**
         * @brief Ajout d'un paramètre au module.
         *
         * @param le paramètre p au format {"", , , , , }
         */
        void add(parameter p);
        /**
         * @brief Construit le texte destiné à être affiché pour les IO
         */
        void setMenu();
        /**
         * @brief Méthode MIDI spécifique au module.
         */
        virtual void handleNoteOn(byte channel, byte pitch, byte velocity) {} 
        /**
         * @brief Méthode MIDI spécifique au module.
         */
        virtual void handleNoteOff(byte channel, byte pitch, byte velocity) {}
        /**
         * @brief Méthode MIDI spécifique au module.
         */
        virtual void handleClock() {}
        /**
         * @brief Méthode MIDI spécifique au module.
         */
        virtual void handleStart() {}
        /**
         * @brief Méthode MIDI spécifique au module.
         */
        virtual void handleStop() {}
        /**
         * @brief Méthode MIDI spécifique au module.
         */
        void panic() {
            if(2 < this->io[1].value) {
                clear_channel(this->io[1].value - 2);
                this->io[1].value = 2;
            }
        }
        /**
         * @brief Méthode de l'encodeur spécifique au module.
         */
        virtual void l_handlePress();
        /**
         * @brief Méthode de l'encodeur spécifique au module.
         */
        virtual void r_handlePress();
        /**
         * @brief Méthode définissant la chaîne affichée.
         *
         * @param val est la valeur du paramètre
         * @param temp est la chaîne
         *
         * @remark Dépend du numéro de curseur Display::cursor_num 
         */
        virtual void getString(int val, char temp[8]) {}
        /**
         * @brief Méthode lancée à chaque boucle.
         */ 
        virtual void execute() {}

};

#endif

