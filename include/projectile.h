#ifndef projectile_h
#define projectile_h

#include "world/level.h"
#include "directions.h"

class Projectile {
public:
    Projectile();
    Projectile(Level l);
    void move();
    bool isDone();
private:
    Level* lvl;
    Square* curSquare;
    Direction dir;
    bool isDone;
};

#endif
