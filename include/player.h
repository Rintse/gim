#ifndef player_h
#define player_h

#include "world/world.h"
#include "world/level.h"
#include "directions.h"
#include "actions.h"

class Player {
public:
    Player();
    Player(World w);
    void act(Action a);
    void move(Direction dir);
private:
    World* world;
    Level* curLvl;
    Square* curSquare;
    Direction facing;
};

#endif
