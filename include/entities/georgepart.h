#ifndef georgepart_h
#define georgepart_h

#include "tools/key_input.h"

class Level;
class Square;

class GeorgePart {
public:
    GeorgePart();
    GeorgePart(Level* l, Square* s);

    virtual void act(Input i) = 0;
    virtual char token() = 0;

protected:
    Square* curSquare;
    Level* lvl;
};

#endif