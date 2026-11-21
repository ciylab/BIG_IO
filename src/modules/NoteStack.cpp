/**
 * @file NoteStack.cpp
 */

#include "NoteStack.h"


bool NoteStack::isEmpty() {
    return size == 0;
}

bool NoteStack::isFull() {
    return size == 15;
}

void NoteStack::push(byte pitch) {
    if(!isFull()) {
        notes[size] = pitch;
    }
    size++;
}

void NoteStack::remove(byte pitch) {
    int i = 0;
    while(i < size && notes[i] != pitch) {
        i++;
    }
    if(i == size) {
        return;
    }
    while(i < size) {
        notes[i] = notes[i + 1];
        i++;
    }
    size--;
}

byte NoteStack::top() {
    if(!isEmpty()) {
        return notes[size - 1];
    }
    return -1;
}

void NoteStack::printStack() {
    Serial.print("| ");
    for(int i = 0; i < size; i++) {
        Serial.print(notes[i], HEX);
        Serial.print(", ");
    }
    Serial.println();
}
