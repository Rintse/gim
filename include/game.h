#ifndef game_h
#define game_h

#include "entities/player.h"
#include "world/level.h"
#include "generation/levelgenerator.h"
#include "gfx.h"
#include "tools/key_input.h"
#include <vector>

#define FPS 25.0
#define FRAMETIME (1000.0/FPS)
#define LVL_HEIGHT 30
#define LVL_WIDTH 50
#define SPRITE_DIM 16

class Game {
    public:
        Game();
        ~Game();
        void setLevel(Level* l);
        Level* getLevel();
        void addLevel(Level* l);
        Level* newLevel(int width, int height, Direction dir, int viewDistance);
        FastRandom* getRNG();
        int init();
        void run();
        void over();

    private:
        GFX gfx;
        KeyHandler* kh;
        FastRandom randgen;
        Player* player;
        Level *curLvl;
        Level* prevLvl;
        std::vector<Level*> levels;
        LevelGenerator levelgen;
        bool gameOver;
        bool paused;
};

#endif
