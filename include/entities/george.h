#ifndef george_h
#define george_h

#include "tools/directions.h"
#include "game.h"

#define COOLDOWN_SECONDS 1
#define ROUND_SECONDS 20
#define COOLDOWN_FRAMES (FPS*COOLDOWN_SECONDS)
#define ROUND_FRAMES (FPS*ROUND_SECONDS)

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

    void attackBullets();
    void attackLasers();
    void attackTinyGeorges();
    void shootBullet(Square* s);
    void shootLaser(Square* s);
};

#endif
