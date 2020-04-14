#ifndef player_h
#define player_h

#include "world/world.h"
#include "directions.h"

class Player {
public:
    Player();
    Player(World w);
    void move(Direction dir);
private:
    World world;
    Level curLvl;
    int x;
    int y;
};

#endif
