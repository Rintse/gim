#ifndef game_h
#define game_h

#include "player.h"
#include "world/level.h"
#include "screen.h"

#define FPS 20.0
#define FRAMETIME (1000.0/FPS)
#define LVL_HEIGHT 20
#define LVL_WIDTH 30

class Game {
    public:
        Game();
        void init();
        void run();
    private:
        Player* player;
        Level *curLvl;
        Screen screen;
        bool gameOver;
};

#endif
