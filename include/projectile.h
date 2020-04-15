#ifndef projectile_h
#define projectile_h

#include "directions.h"

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
