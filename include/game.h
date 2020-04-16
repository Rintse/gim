#ifndef game_h
#define game_h

#include "entities/player.h"
#include "world/level.h"
#include "gfx.h"
#include "tools/key_input.h"
#include <vector>

#define FPS 30.0
#define FRAMETIME (1000.0/FPS)
#define LVL_HEIGHT 20
#define LVL_WIDTH 30

class Game {
    public:
        Game();
        ~Game();
        void setLevel(Level* l);
        Level* getLevel();
        void addLevel(Level* l);
        FastRandom* getRNG();
        void init();
        void run();

    private:
        GFX gfx;
        KeyHandler* kh;
        FastRandom randgen;
        Player* player;
        Level *curLvl;
        std::vector<Level*> levels;
        //Screen screen;
        //InputHandler inputHandler;
        bool gameOver;
};

#endif
