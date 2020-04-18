#include "entities/projectiles/projectile.h"
#include "world/squares/square.h"
#include "world/level.h"
#include <iostream>

Projectile::Projectile() {}

Projectile::Projectile(Level* l, Square* s, Direction d) {
    lvl = l;
    curSquare = s;
    dir = d;
}

Square* Projectile::getCurSquare() {
    return curSquare;
}

int Projectile::move() {
    for(int i = 0; i < 2; i++) {
        Square* s = lvl->getSquareDir(curSquare, dir);
        if(s == 0) return 0;
        // Only travel along floor squares
        if(s->type() != SQUARE_FLOOR) {
            return -1;
        }
        else {
            // Kill an enemy when moving onto its square
            if(s->getEnemy() != 0) {
                lvl->removeEnemy(s->getEnemy());
                s->setEnemy(0);
            }

            // Move onto the square
            curSquare->setProjectile(0);
            s->setProjectile(this);
            curSquare = s;
        }
    }

    return 0;
}
