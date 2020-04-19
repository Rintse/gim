#ifndef georgeparts_h
#define georgeparts_h

#include "georgegun.h"
#include "georgenogun.h"

class GeorgeA : public GeorgeNoGun {
public:
    GeorgeA();
    GeorgeA(Level* l, EmptySquare* s);

    char token();
};

class GeorgeB : public GeorgeNoGun {
public:
    GeorgeB();
    GeorgeB(Level* l, EmptySquare* s);

    char token();
};

class GeorgeC : public GeorgeNoGun {
public:
    GeorgeC();
    GeorgeC(Level* l, EmptySquare* s);

    char token();
};

class GeorgeD : public GeorgeGun {
public:
    GeorgeD();
    GeorgeD(Level* l, EmptySquare* s);

    char token();
};

class GeorgeE : public GeorgeNoGun {
public:
    GeorgeE();
    GeorgeE(Level* l, EmptySquare* s);

    char token();
};

class GeorgeF : public GeorgeGun {
public:
    GeorgeF();
    GeorgeF(Level* l, EmptySquare* s);

    char token();
};


#endif
