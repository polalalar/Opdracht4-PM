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
    speeltTegenRobot = false;
    // breedte = 3;
    // hoogte = 2;
    // vakje* vorigeRijIngang = nullptr;
    // for (int i = 0; i < hoogte; i++) {
    //     vakje* rijPtr = gobordMaakRij (breedte);
    //     if (i == 0) {
    //         ingang = rijPtr;
    //     } // if
    //     else {
    //         verbindRijen(vorigeRijIngang,rijPtr);
    //     } // else
    //     vorigeRijIngang = rijPtr;
    // } // for
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

void gobord::maakGobord (int nieuweHoogte, int nieuweBreedte) {
    hoogte = nieuweHoogte;
    breedte = nieuweBreedte;
    vakje* vorigeRijIngang = nullptr;
    for (int i = 0; i < hoogte; i++) {
        vakje* rijPtr = gobordMaakRij(breedte);
        if (i == 0) {
            ingang = rijPtr;
        } // if
        else {
            verbindRijen(vorigeRijIngang,rijPtr);
        } // else
        vorigeRijIngang = rijPtr;
    } // for
} // gobord::maakGobord

void gobord::verwijderGobord ( ) {
    cout << "CLEAN UP" << endl;
    if (ingang == nullptr) {
        return;
    } // if
    vakje* nuRij = ingang;
    vakje* volgendeRij = ingang->buren[4];
    verwijderRij(nuRij);
    while (volgendeRij != nullptr) {
        nuRij = volgendeRij;
        volgendeRij = volgendeRij->buren[4];
        verwijderRij(nuRij);;
    } // while
} //gobord::verwijderGobord

void gobord::verwijderRij (vakje* rij) {
    vakje* vorigVakje = nullptr;
    vakje* nuVakje = rij;
    for (int i = 0; i < breedte; i++) {
        vorigVakje = nuVakje;
        nuVakje = nuVakje->buren[2];
        delete vorigVakje;
    } // for
} // gobord::verwijderRij

void gobord::print ( ) {
    cout << "goborden zien er mooi uit." << endl;
    vakje* nuRij = ingang;
    vakje* volgendeRij = ingang->buren[4];
    printRij(nuRij);
    while (volgendeRij != nullptr) {
        nuRij = volgendeRij;
        volgendeRij = volgendeRij->buren[4];
        printRij(nuRij);
    } // while
} //gobord::print

void gobord::printRij (vakje* rij) {
    vakje* vorigVakje = nullptr;
    vakje* nuVakje = rij;
    for (int i = 0; i < breedte; i++) {
        vorigVakje = nuVakje;
        nuVakje = nuVakje->buren[2];
        cout << vorigVakje->kleur;
    } // for
    cout << endl;
} // gobord::printRij

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