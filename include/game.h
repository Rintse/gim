#ifndef game_h
#define game_h

#include "player.h"
#include "world/world.h"
#include "screen.h"

enum ACTION {
    NONE, MOVEUP, MOVELEFT, MOVEDOWN, MOVERIGHT, SHOOT
};

class Game {
    public:
        Game();
        void run();
    private:
        Player player;
        World world;
        Screen screen;
        bool gameOver;
};

#endif
