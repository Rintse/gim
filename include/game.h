#ifndef game_h
#define game_h

#include "player.h"
#include "world/world.h"
#include "screen.h"

class Game {

private:
    Player player;
    World world;
    Screen screen;
};

#endif
