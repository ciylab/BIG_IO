/**
 * @class Display
 * @file Display.h
 * @brief Group of parameters and functions for oled screen.
 *
 * For real time midi, cv and gate we choose to write at most one 
 * character by loop.
 */
 

#ifndef DISPLAY_H
#define DISPLAY_H
#include <Arduino.h>
#include "Module.h"

class Display {
    public:
        /**
         * From 0 (top left) to 7 (bottom right).
         */
        static byte cursor_num;
        /**
         * From 0 to 63 for '>'.
         */
        static byte cursor_pos;
        /**
         * char are wrote one by one.
         */
        static char buffer[64];
        /**
         * what we can see.
         */
        char screen[64];
        /**
         * current position on screen
         */
        static byte charIndex;
        /**
         * the last position to write
         */ 
        static byte endPosition;
        /**
         * @brief TEXT_SIZE spaces.
         */
        Display();
        /**
         * @brief font and welcome
         */
        void begin();
        /**
         * write one char
         *
         * @param position from 0 to 63
         * @param c the char
         */
        void static putChar(byte position, char c);
        /**
         * By CIYLab and version.
         */
        void welcome();
        /**
         * @brief the main function to write text char by char.
         */
        void display();
        /**
         * @brief To prepare buffer for next page.
         */
        void static newPage();
        /**
         * @brief Use getString to show the parameter value.
         *
         * @param val value to show on screen
         */
        void static show_value(int val);
        /**
         * @brief Use parameter name
         */
        void static show_name();
        /**
         * @brief Print a 7 chars word at **cursor_pos**
         */
        static void print_here(char *word);
};

#endif
