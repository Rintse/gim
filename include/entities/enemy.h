#ifndef enemy_h
#define enemy_h

#include "tools/directions.h"
#include "tools/actions.h"
#include "tools/pathfind.h"

class Level;
class EmptySquare;

#define LOCKOUTFRAMES 3

class Enemy {
public:
    Enemy();
    Enemy(Level* l, EmptySquare* s);
    int act();
    int move(Direction dir);
    EmptySquare* getCurSquare();
    char token();

private:
    BFS pathfind;
    Level* lvl;
    EmptySquare* curSquare;
    Action nextMove;
    Direction facing;
    int lockout;
};

#endif
