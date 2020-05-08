#ifndef georgepart_h
#define georgepart_h

#include "tools/key_input.h"
#include "tools/directions.h"

class Level;
class EmptySquare;

class GeorgePart {
public:
    GeorgePart();
    GeorgePart(Level* l, EmptySquare* s, char t);
    virtual ~GeorgePart() {};

    virtual void act(Input i) = 0;
    char token();

    EmptySquare* getSquare();

protected:
    EmptySquare* curSquare;
    Level* lvl;
    char georgeToken;

    void move(Direction dir);
};

#endif
