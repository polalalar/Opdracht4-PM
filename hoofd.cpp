// file hoofd.cc
#include <iostream>
#include "gobord.h"
using namespace std;
// Opdracht 3 - Programmeermethoden - Nonogrammen
// Authors: Jens van der Linden & Thijmen Rosenbrand
// Student Numbers: s5205212 & s5225752
// Compiled with: g++ 13.3.0
// Version: 1.0
// Last edited: 09-11-2026

// Print an info block with information about the program and the authors
void infoblock() {
    cout << "-----------------------------------------------------------"
        << endl
        << "Authors          | Jens van der Linden | Thijmen Rosenbrand"
        << endl 
        << "-----------------------------------------------------------"
        << endl
        << "Student Numbers  |      s5205212       |     s5225752      "
        << endl
        << "-----------------------------------------------------------"
        << endl
        << "Year of arrival  |        2026         |       2026        "
        << endl
        << "-----------------------------------------------------------"
        << endl
        << "Last edited : 09-11-2026." << endl
        << "Assignment 3 - Programeermethoden - Nonogrammen." 
        << endl
        << "-----------------------------------------------------------"
        << endl
        << "This program lets the user (manually or pseudo-randomly) "
        << "create nonograms."
        << endl
        << "It offers an editor to create and solve nonograms."
        << endl
        << "In addition there is a menu to configure all nonogram settings,"
        << endl
        << "and another menu to save/load a nonogram's hints to/from files."
        << endl
        << "-----------------------------------------------------------"
        << endl
        << "The hints are shown using 1 to 9 when dealing with numbers below 10,"
        << endl
        << "for numbers 10 to 35 a to z are used,"
        << "and for numbers 35 to 60 A to Z are used."
        << endl << endl << endl;
} // infoblock

// Check if a character is a number (0-9)
bool isNumber(char inputChar) {
    return (inputChar >= '0' && inputChar <= '9');
} // isNumber

// Check if a character is a letter (a-z or A-Z)
bool isLetter(char kar) {
    return (kar >= 'a' && kar <= 'z') || (kar >= 'A' && kar <= 'Z');
} // isLetter

// Reads a number from the user, with a maximum number
int readNumber(int max_num = 10000, int min_num = 1) {
    int num = 0; // number to return
    int max_num_reached = false; // flag to stop after reaching max_num
    int next_num = 0; // next number to check if it exceeds max_num
    char kar = cin.get(); // get the first character from input
    
    // Remove leading newlines
    while (kar == '\n') {
        kar = cin.get();
    } // while
    while (kar != '\n') { // Read until newline is found
        // Discard numbers after max is reached
        if (isNumber(kar) && !max_num_reached) {
            next_num = num * 10 + kar - '0';
            if (next_num <= max_num) {
                num = next_num;
            } // if
            else {
                max_num_reached = true;
            } // else
        } // if
        kar = cin.get(); // next iteration
    } // while
    return num;
} // readNumber

char getMenuChoice() {
    char choice = cin.get(); // user input for menu choice
    while (!isLetter(choice)) {
        choice = cin.get();	
    } // while

    // Convert choice to lowercase if appliccable
    if (choice >= 'A' && choice <= 'Z') {
        choice += 'a' - 'A'; // A is before a in ASCII
    } // if
    return choice;
} // getMenuChoice

void speelZet (gobord nuGobord) {
    cout << "Geef de hoogte van het vakje" << endl << ">";
    int hoogte = readNumber(nuGobord.hoogte - 1);
    cout << "Geeft de breedte van het vakje" << endl << ">";
    int breedte = readNumber(nuGobord.breedte - 1);
    nuGobord.speelZet(hoogte, breedte, 'w');
    cout << "Speel een zet op (" << hoogte << "," << breedte << ")" << endl;
}

int main ( ) {
    gobord nuGobord;
    int nieuweHoogte = 0;
    int nieuweBreedte = 0;
    cout << "Hoe hoog is het bord?" << endl << ">";
    nieuweHoogte = readNumber();
    cout << "Hoe breed is het bord?" << endl << ">";
    nieuweBreedte = readNumber();
    nuGobord.maakGobord(nieuweHoogte,nieuweBreedte);
    cout << "Wil je tegen een computer spelen (J/N)?" << endl << ">";
    char choice = getMenuChoice();
    if (choice == 'j') {
        nuGobord.speeltTegenRobot = true;
    }
    bool stop = false; // flag om het programma te stoppen

    while (true) {
        nuGobord.print( );
        cout << "-------------------< Menu >-------------------" << endl;
        cout << "[Z]et, [S]top" << endl;
        choice = getMenuChoice();
        switch (choice) {
        case 'z':
            speelZet(nuGobord);
            break;
        case 's':
            stop = true;
            break;
        default:
            cout << "Invalid choice of " << choice << endl;
        } // switch
        if (stop) { // gebruiker wilt stoppen
            cout << "Weet je zeker dat je wilt stoppen? (J/N)" << endl;
            choice = getMenuChoice();
            if (choice == 'j') {
                break;
            } // if
            else {
                stop = false;
            } // else
        } // if
    } // while
    nuGobord.verwijderGobord();
    return 0;
}//main
