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
    breedte = 3;
    hoogte = 2;
    vakje* rijArray[hoogte];
    for (int i = 0; i < hoogte; i++) {
        rijArray[i] = gobordMaakRij (breedte);
    } // for
    ingang = rijArray[0];

    // hoogte -1 omdat je de rij met degene erna verbind en anders
    // ga je buiten de array
    for (int i = 0; i < hoogte - 1; i++) {
        verbindRijen(rijArray[i],rijArray[i+1]);
    } // for
    
}//gobord::gobord

vakje* gobord::gobordMaakRij (int breedte) {
    vakje* rijIngang = nullptr;
    vakje* vorig_vakje = nullptr;
    for (int i = 0; i < breedte; i++) {
        vakje* nieuw_vakje = new vakje;
        
        if (i == 0) {
            rijIngang = nieuw_vakje;
            nieuw_vakje->buren[6] = nullptr;
        } // if
        else {
            nieuw_vakje->buren[6] = vorig_vakje;
            vorig_vakje->buren[2] = nieuw_vakje;
        } // else

        nieuw_vakje->buren[0] = nullptr;
        nieuw_vakje->buren[1] = nullptr;
        nieuw_vakje->buren[2] = nullptr;
        nieuw_vakje->buren[3] = nullptr;
        nieuw_vakje->buren[4] = nullptr;
        nieuw_vakje->buren[5] = nullptr;
        // 6 niet omdat die hierboven gedaan wordt.
        nieuw_vakje->buren[7] = nullptr;

        vorig_vakje = nieuw_vakje;
    } // for
    return rijIngang;
} // gobord::gobordMaakRij


// verbind de rijen met elkaar
void gobord::verbindRijen (vakje* ingangBoven,vakje* ingangOnder) {
    // verbind de boven en onderkant
    vakje* BovenHulp = ingangBoven;
    vakje* OnderHulp = ingangOnder;
    for (int i = 0; i < breedte; i++) {
        BovenHulp->buren[4] = OnderHulp;
        OnderHulp->buren[0] = BovenHulp;

        BovenHulp = BovenHulp->buren[2];
        OnderHulp = OnderHulp->buren[2];
    } // for

    // nadat de for loop klaar is zijn BovenHulp en OnderHulp nullptr's

} // gobord::verbindRijen

gobord::gobord (int hoogte, int breedte) {
    // TODO
} // gobord::gobord

gobord::~gobord ( ) {
    cout << "CLEAN UP" << endl;
    vakje* rijArray[hoogte];
    vakje* hoogteHulp = ingang;
    // beweegt naar beneden door het bord.
    for (int i = 0; i < hoogte; i++) {
        rijArray[i] = hoogteHulp;
        // niet de laatste
        if (i != hoogte - 1) {
            hoogteHulp = hoogteHulp->buren[4];
        } // if
    } // for
    hoogteHulp = nullptr;

    for (int i = 0; i < hoogte; i++) {
        vakje* rijIngang = rijArray[i];
        vakje* alleVakjesInRij[breedte];
        // beweegt naar rechts
        for (int j = 0; j < breedte; j++) {
            alleVakjesInRij[j] = rijIngang;
            rijIngang = rijIngang->buren[2];
        } // for
        rijIngang = nullptr;
        // delete alle vakjes
        for (int j = 0; j < breedte; j++) {
            delete alleVakjesInRij[j];
        } // for
    } // for
    
    // geen delete ingang nodig omdat die hierboven al verwijderd wordt.
}//gobord::~gobord

void gobord::print ( ) {
    cout << "goborden zien er mooi uit." << endl;
    // TODO
}//gobord::print

// TODO