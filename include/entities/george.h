#ifndef george_h
#define george_h

#include "tools/directions.h"

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

    void attackBullets();
    void attackLasers();
    void attackTinyGeorges();
    void shootBullet(Square* s);
    void shootLaser();
};

#endif
