#ifndef projectile_h
#define projectile_h

#include "tools/directions.h"

class Level;
class Square;

class Projectile {
public:
    Projectile();
    Projectile(Level* l, Square* s, Direction d, bool p);
    int move();
    char token();
    Square* getCurSquare();
private:
    Level* lvl;
    Square* curSquare;
    Direction dir;
    bool player;
};

#endif
