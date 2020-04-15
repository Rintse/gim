#ifndef enemy_h
#define enemy_h

#include "world/world.h"
#include "world/level.h"
#include "directions.h"
#include "actions.h"

class Enemy {
public:
    Enemy();
    Enemy(World w);

    Action decideMove(); //Can be done in parralel
    void act();
private:
    World* world;
    Level* curLvl;
    Square* curSquare;
    Action nextMove;
};

#endif
