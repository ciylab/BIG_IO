/**
 * @file config.h
 * @brief Fichier de configuration du projet.
 */
#ifndef CONFIG_H
#define CONFIG_H
#include <Arduino.h>

#define CLOCK_IN PA3   //!< pin d'entrée d'horloge fixe
#define CLOCK_OUT PB3  //!< pin de sortie d'horloge fixe
#define GATE_1 PB5     //!< pin de sortie de gate assignable
#define GATE_2 PB4     //!< pin de sortie de gate assignable 
#define DRUM_2 PB8     //!< pin de sortie de drum assignable 
#define DRUM_1 PB9     //!< pin de sortie de drum assignable 


#define MAIN 0 // pratique pour se repérer dans le code
#define PLAY 1 // pratique pour se repérer dans le code
#define TIME 2 // pratique pour se repérer dans le code

/**
 * @brief liste des leds de sorties 
 *
 * Dans l'odre du clignotement simple au démarrage du module 
 * eurorack (test).
 */
const byte pins[] = {
    CLOCK_OUT, DRUM_1, DRUM_2, GATE_1, GATE_2};

/**
 * @brief structure d'un paramètre.
 *
 * Un paramètre est modifié par les encodeurs. Pour un module donné
 * il est identifié par son rang et affiché à la position du curseur
 * de navigation (>) **cursor_num**.
 */
typedef struct parameter {
    char name[8];    //!<  name to display
    byte value;      //!<  uses when playing
    byte buffer;     //!<  value sometimes used to prevent bug on change
    byte min;        //!<  min value often 0
    byte max;        //!<  max value
    byte cursor_pos; //!<  on screen from 0 to 63
} parameter;

/**
 * @brief L'action détermine la classe fille.
 *
 * Utilisé pour les fonctions load et save de l'eeprom.
 */
typedef struct algo {
    byte in;
    byte out;
    byte action; //<! Numéro dans la liste des différents modules codés
} algo;

/**
 * @brief Les 5 sorties sont mises à HIGH par défaut.
 *
 * @remark Les leds sont éteintes car les transistors qui servent
 * de switch mesurent 5 volts quand la sortie est LOW. C'est une 
 * conséquence du montage car le potentiel de référence 
 * à la sortie du transistor est la terre.
 */
void pin_init();

/**
 * @brief Activation de la guirlande de leds au démarrage.
 *
 * Si une led ne s'allume pas alors il y a un bug.
 */
void pin_test();
#endif
