#ifndef george_h
#define george_h

#include "game.h"
#include "georgeparts.h"

#define COOLDOWN_SECONDS 1
#define ROUND_SECONDS 20
#define COOLDOWN_FRAMES (FPS*COOLDOWN_SECONDS)
#define ROUND_FRAMES (FPS*ROUND_SECONDS)

#define N_PARTS 6

class Level;
class Square;

class George {
public:
    George();
    George(Level* l, Square* s);

    void act();

private:
    Square* curSquare;
    Level* lvl;
    int curRound;
    int frame;
    int health;

    GeorgePart* parts[N_PARTS];

    void setParts();
    void attackBullets();
    void attackLasers();
    void attackTinyGeorges();
};

#endif
