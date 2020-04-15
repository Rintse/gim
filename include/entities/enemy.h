#ifndef enemy_h
#define enemy_h

#include "tools/directions.h"
#include "tools/actions.h"

class Level;
class Square;

class Enemy {
public:
    Enemy();
    Enemy(Level* l, Square* s);

    Action decideMove(); //Can be done in parralel
    void act();
private:
    Level* lvl;
    Square* curSquare;
    Action nextMove;
};

#endif
