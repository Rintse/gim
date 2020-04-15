#ifndef game_h
#define game_h

#include "player.h"
#include "world/world.h"
#include "screen.h"

#define FPS 20.0
#define FRAMETIME (1000.0/FPS)

class Game {
    public:
        Game();
        void run();
    private:
        Player* player;
        Level *curLvl;
        Screen screen;
        bool gameOver;
};

#endif
