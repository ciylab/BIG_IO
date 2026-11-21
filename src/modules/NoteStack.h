/**
 * @class NoteStack
 * @brief CV/gate is monophonic so we need to memorize note on
 */

#ifndef NOTESTACK_H
#define NOTESTACK_H
#include <Arduino.h>

class NoteStack {
    private:
        byte size;
        byte notes[16];
    public:
        NoteStack() {
            size = 0;
        }
        bool isEmpty();
        bool isFull();
        void push(byte pitch);
        void remove(byte pitch);
        byte top();
        // to debug
        void printStack();
};

#endif
