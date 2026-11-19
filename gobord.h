// file gobord.h
class vakje {
    public:
        char kleur;       //     7 0 1
        vakje* buren[8];  //     6   2
        vakje ( );        //     5 4 3
};//bordvakje

class gobord {
    private:
        vakje* ingang;
        int height, width;
        // TODO
    public:
        gobord ( );
        gobord (int hoogte, int breedte);
        ~gobord ( );
        void print ( );
        // TODO
};//gobord
