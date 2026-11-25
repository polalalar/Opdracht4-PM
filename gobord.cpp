// file gobord.cc
#include <iostream>
#include "gobord.h"
using namespace std;


vakje::vakje ( ) {
    kleur = 'a';
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

    // verbind de rijen schuin met elkaar (1,3,5,7)
    // dat is niet nodig als de breedte minder dan 2 is
    if (breedte < 2) {
        return;
    }
    vakje* LinksBovenHulp = ingangBoven;
    vakje* LinksOnderHulp = ingangOnder;
    // je weet zeker dat buur[2] bestaat door de if hierboven
    vakje* RechtsBovenHulp = ingangBoven->buren[2];
    vakje* RechtsOnderHulp = ingangOnder->buren[2];

    for (int i = 0; i < breedte - 1; i++) {
        verbindVier(LinksBovenHulp, LinksOnderHulp, RechtsBovenHulp, RechtsOnderHulp);
        // verschuif naar rechts.
        LinksBovenHulp = LinksBovenHulp->buren[2];
        LinksOnderHulp = LinksOnderHulp->buren[2];
        // deze worden nullptr's op de laatste iteratie
        RechtsBovenHulp = RechtsBovenHulp->buren[2];
        RechtsOnderHulp = RechtsOnderHulp->buren[2];
    }

} // gobord::verbindRijen

void gobord::verbindVier (vakje* LinksBoven, vakje* LinksOnder, vakje* RechtsBoven, vakje* RechtsOnder) {
    // LinksBoven <-> RechtsOnder
    LinksBoven->buren[3] = RechtsOnder;
    RechtsOnder->buren[7] = LinksBoven;
    // RechtsBoven <-> LinksOnder
    RechtsBoven->buren[5] = LinksOnder;
    LinksOnder->buren[1] = RechtsBoven;
} // gobord::verbindVier

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
    vakje* rijArray[hoogte];
    vakje* hoogteHulp = ingang;
    // beweegt naar beneden door het bord.
    vakje* gevonden = krijgVakje(1,1);
    if (gevonden != nullptr) {
        gevonden->kleur = '0';
    }
    
    for (int i = 0; i < hoogte; i++) {
        rijArray[i] = hoogteHulp;
        // niet de laatste
        if (i != hoogte - 1) {
            hoogteHulp = hoogteHulp->buren[4];
        } // if
    } // for
    hoogteHulp = nullptr;
    for (int i = 0; i < hoogte; i++) {
        vakje* ptr = rijArray[i];
        for (int j = 0; j < breedte; j++) {
            char kar = ptr->kleur;
            cout << kar;
            ptr = ptr->buren[2];
        } // for
        cout << endl;
    } // for
} //gobord::print

vakje* gobord::krijgVakje (int m, int n) {
    if (m < 0 || m >= hoogte) {
        return nullptr;
    } // if

    if (n < 0 || n >= breedte) {
        return nullptr;
    } // if
    // het vakje dat we zoeken zit in het speel veld.
    vakje* vak = ingang;
    // beweeg naar beneden
    for (int i = 0; i < m; i++) {
        vak = vak->buren[4];
    } // for
    // beweeg naar rechts
    for (int i = 0; i < n; i++) {
        vak = vak->buren[2];
    } // for

    return vak;
}

// TODO