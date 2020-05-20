#ifndef george_h
#define george_h

#include "georgenogun.h"
#include "georgegun.h"
#include "tools/fastrandom.h"

// bossfight phase length
#define COOLDOWN_SECONDS 2
#define ROUND_SECONDS 10
#define BULLET_PAUSE 10

// george size
#define HEIGHT 3
#define WIDTH 7
#define N_PARTS HEIGHT * WIDTH

// other
#define N_TINYBABYGEORGES 10
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
    bool cooldown;

    void setParts();
    void inputToParts();
    void attackBullets();
    void attackLasers();
    void attackTinyGeorges();
    void spawnGeorges();
    Action avoidPlayer();
    Action followPlayer();
    bool setRound();
    void advanceRound();
};

#endif
