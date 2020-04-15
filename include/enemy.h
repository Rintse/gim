#ifndef enemy_h
#define enemy_h

#include "directions.h"
#include "actions.h"

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
