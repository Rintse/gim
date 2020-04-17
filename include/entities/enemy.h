#ifndef enemy_h
#define enemy_h

#include "tools/directions.h"
#include "tools/actions.h"
#include "tools/pathfind.h"

class Level;
class Square;

class Enemy {
public:
    Enemy();
    Enemy(Level* l, Square* s);

    Action decideMove();
    void act();
private:
    BFS pathfind;
    Level* lvl;
    Square* curSquare;
    Action nextMove;
    Direction facing;
};

#endif
