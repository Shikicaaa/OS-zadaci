#include <iostream>
class Klasa{
    Klasa();
    ~Klasa();
    Klasa(Klasa& obj);

    public:
        int a;
        int b;
        inline int saberiBrojeve(int prvi, int drugi) {return prvi + drugi;}
};