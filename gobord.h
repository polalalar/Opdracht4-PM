// file gobord.h
class vakje {
    public:
        char kleur;       //     7 0 1
        vakje* buren[8];  //     6   2
        vakje ( );  //     5 4 3
};//bordvakje

class gobord {
    private:
        vakje* ingang;
        // TODO
    public:
        int breedte, hoogte;
        bool speeltTegenRobot;
        gobord ( );
        void maakGobord (int hoogte, int breedte);
        vakje* gobordMaakRij (int breedte);
        void verbindRijen (vakje* ingangBoven, vakje* ingangOnder);
        void verbindVier (vakje* LinksBoven, vakje* LinksOnder, vakje* RechtsBoven, vakje* RechtsOnder);
        vakje* krijgVakje (int m, int n);
        void verwijderRij (vakje* rij);
        void printRij (vakje* rij);
        void verwijderGobord ( );
        void speelZet (int hoogte, int breedte, char kleur);
        void print ( );
        // TODO
};//gobord
