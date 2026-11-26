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
        int breedte, hoogte;
        // TODO
    public:
        gobord ( );
        gobord (int hoogte, int breedte);
        vakje* gobordMaakRij (int breedte);
        void verbindRijen (vakje* ingangBoven, vakje* ingangOnder);
        void verbindVier (vakje* LinksBoven, vakje* LinksOnder, vakje* RechtsBoven, vakje* RechtsOnder);
        vakje* krijgVakje (int m, int n);
        void verwijderRij (vakje* rij);
        ~gobord ( );
        void print ( );
        // TODO
};//gobord
