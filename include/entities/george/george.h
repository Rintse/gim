#ifndef george_h
#define george_h

#include "georgeparts.h"
#include "tools/fastrandom.h"

// bossfight phase length
#define COOLDOWN_SECONDS 1
#define ROUND_SECONDS 20

// george size
#define N_PARTS 6
#define WIDTH 3

// other
#define N_TINYBABYGEORGES 12
#define HEALTH 40

class Level;
class Square;

class George {
public:
    George();
    George(Level* l, EmptySquare* s, int FPS);
    ~George();

    void act();
    bool takehit();
    int getHP();

private:
    EmptySquare* curSquare;
    Level* lvl;
    GeorgePart* parts[N_PARTS];
    Round curRound;
    Direction dir;
    Input input;
    FastRandom* fs;

    int frame;
    int health;
    int cooldownFrames;
    int roundFrames;
    int lvlWidth;
    int lvlHeight;

    void setParts();
    void inputToParts();
    void attackBullets();
    void attackLasers();
    void attackTinyGeorges();
    void spawnGeorges();
    Action avoidPlayer();
    Action followPlayer();
};

#endif
