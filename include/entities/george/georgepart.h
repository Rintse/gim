#ifndef georgepart_h
#define georgepart_h

#include "tools/key_input.h"
#include "tools/directions.h"

class Level;
class Square;

class GeorgePart {
public:
    GeorgePart();
    GeorgePart(Level* l, Square* s);

    virtual void act(Input i) = 0;
    virtual char token() = 0;

    Square* getSquare();

protected:
    Square* curSquare;
    Level* lvl;

    void move(Direction dir);
};

#endif
