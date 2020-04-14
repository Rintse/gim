#ifndef player_h
#define player_h

#include "world/world.h"

class Player {
public:
    Player(World w);
    int move(int direction);
private:
    World world;
    Level curLvl;
    int x;
    int y;
};

#endif
