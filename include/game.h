#ifndef game_h
#define game_h

#include "entities/player.h"
#include "world/level.h"
#include "generation/levelgenerator.h"
#include "gfx/gfx.h"
#include "tools/key_input.h"
#include <vector>

#define FPS 25.0
#define FRAMETIME (1000.0/FPS)
#define LVL_HEIGHT 30
#define LVL_WIDTH 50
#define SPRITE_DIM 16

enum Gamestate {
    STATE_RUN,
    STATE_PAUSED,
    STATE_START,
    STATE_CLOSED,
    STATE_WON,
    STATE_LOST
};

class Game {
    public:
        Game();
        ~Game();
        void setLevel(Level* l);
        Level* getLevel();
        Level* getStartLevel();
        void addLevel(Level* l);
        Level* newLevel(Level* neighbour, int width, int height, Direction dir, int viewDistance);
        FastRandom* getRNG();
        int init();
        void interfaceInputs(Input in);
        void run();
        void over(bool won);

    private:
        GFX gfx;
        KeyHandler* kh;
        FastRandom randgen;
        Player* player;
        Level *curLvl;
        Level* prevLvl;
        Level* startLvl;
        std::vector<Level*> levels;
        LevelGenerator levelgen;
        Gamestate state;
};

#endif
