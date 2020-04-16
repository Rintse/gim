#ifndef projectile_h
#define projectile_h

#include "tools/directions.h"
#define PROJECTILE_SPEED 2

class Level;
class Square;

class Projectile {
public:
    Projectile();
    Projectile(Level* l, Square* s, Direction d);
    int move();
    Square* getCurSquare();
private:
    Level* lvl;
    Square* curSquare;
    Direction dir;
};

#endif
