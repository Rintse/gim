#ifndef george_h
#define george_h

#include "georgeparts.h"

#define COOLDOWN_SECONDS 1
#define ROUND_SECONDS 20

#define N_PARTS 6

class Level;
class Square;

class George {
public:
    George();
    George(Level* l, EmptySquare* s, int FPS);

    void act();

private:
    EmptySquare* curSquare;
    Level* lvl;
    GeorgePart* parts[N_PARTS];
    Round curRound;
    Direction dir;
    Input input;

    int frame;
    int health;
    int cooldownFrames;
    int roundFrames;


    void setParts();
    void inputToParts();
    void attackBullets();
    void attackLasers();
    void attackTinyGeorges();
};

#endif
