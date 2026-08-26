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

#include "config.h"
/**
 * Number of characters on screen.
 */
#define TEXT_SIZE 64 

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
        static char buffer[TEXT_SIZE];
        /**
         * what we can see.
         */
        static char screen[TEXT_SIZE];
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
         *
         * @param p the parameter
         */
        void static no_show_value(parameter p);
        /**
         * @brief Print a 7 chars word at **cursor_pos**
         */
        static void print_here(char *word);
};

#endif
