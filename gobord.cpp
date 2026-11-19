// file gobord.cc
#include <iostream>
#include "gobord.h"
using namespace std;


vakje::vakje ( ) {
    kleur = false;
    for (int i = 0; i < 8; i++) {
        buren[i] = nullptr;
    }
}
gobord::gobord ( ) {
    width = 3;
    height = 1;
    vakje* previous_tile = nullptr;
    for (int i=0; i<width; i++) {
        vakje* current_tile = new vakje;
        if (i == 0) {
            ingang = current_tile;
            current_tile->buren[6] = nullptr;
        } // if
        
        else {
            current_tile->buren[6] = new vakje;
            current_tile->buren[6] = previous_tile;
            previous_tile->buren[2] = current_tile;
        } // else
        current_tile->buren[2] = nullptr;

        previous_tile = current_tile;
    } // for
}//gobord::gobord

gobord::gobord (int height, int width) {
    // TODO
} // gobord::gobord

gobord::~gobord ( ) {
    for (int i = 0; i < width; i++) {
        if (i != 0) {
            delete ingang->buren[6];
        } // if
        // delete ingang->buren[0];
        if (i-1 != width) {
            ingang = ingang->buren[2];
        } // if
    } // for
    delete ingang;
}//gobord::~gobord

void gobord::print ( ) {
    cout << "goborden zien er mooi uit." << endl;
    // TODO
}//gobord::print

// TODO