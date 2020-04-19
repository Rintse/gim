#include "entities/projectiles/projectile.h"
#include "world/squares/square.h"
#include "world/level.h"
#include <iostream>

Projectile::Projectile() {}

Projectile::Projectile(Level* l, EmptySquare* s, Direction d) {
    lvl = l;
    curSquare = s;
    dir = d;
    speed = 2;
}

EmptySquare* Projectile::getCurSquare() {
    return curSquare;
}

int Projectile::move() {
    for(int i = 0; i < speed; i++) {
        Square* s = lvl->getSquareDir(curSquare, dir);
        if(s == 0) return 0;
        // Only travel along floor squares
        if(s->type() != SQUARE_FLOOR) {
            return -1;
        }
        else {
            EmptySquare* tmp = dynamic_cast<EmptySquare*>(s);
            // Kill an enemy when moving onto its square
            if(tmp->getEnemy() != 0) {
                lvl->removeEnemy(tmp->getEnemy());
                tmp->setEnemy(0);
            }

            // Move onto the square
            curSquare->setProjectile(0);
            tmp->setProjectile(this);
            curSquare = tmp;
        }
    }

    return 0;
}
