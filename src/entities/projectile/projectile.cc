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

EmptySquare* Projectile::getSquare() {
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
            if(tmp->getGeorgepart() != 0) {
              lvl->hurtGeorge();
              return -1;
            }
            // A player is never hit with his own projectiles
            // When a player is hit by a george projectile he gets hurt
            if(tmp->getPlayer() != 0) {
              tmp->getPlayer()->takeDamage();
            }

            // Move onto the square
            curSquare->setProjectile(0);
            tmp->setProjectile(this);
            curSquare = tmp;
        }
    }

    return 0;
}

Direction Projectile::getDirection() {
    return dir;
}
