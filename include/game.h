#ifndef game_h
#define game_h

#include "entities/player.h"
#include "world/level.h"
#include "screen.h"

#define FPS 25.0
#define FRAMETIME (1000.0/FPS)
#define LVL_HEIGHT 20
#define LVL_WIDTH 30

class Game {
    public:
        Game();
        void setLevel(Level* l);
        FastRandom* getRNG();
        void init();
        void run();
    private:
        FastRandom randgen;
        Player* player;
        Level *curLvl;
        Screen screen;
        bool gameOver;
};

#endif
