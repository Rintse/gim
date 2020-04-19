#ifndef georgepart_h
#define georgepart_h

#include "tools/key_input.h"
#include "tools/directions.h"

class Level;
class EmptySquare;

class GeorgePart {
public:
    GeorgePart();
    GeorgePart(Level* l, EmptySquare* s);

    virtual void act(Input i) = 0;
    virtual char token() = 0;

    EmptySquare* getSquare();

protected:
    EmptySquare* curSquare;
    Level* lvl;

    void move(Direction dir);
};

#endif
