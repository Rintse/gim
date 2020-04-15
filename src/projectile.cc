#include "projectile.h"
#include "world/squares/square.h"
#include "world/level.h"

Projectile::Projectile() {}

Projectile::Projectile(Level* l, Square* s, Direction d) {
    lvl = l;
    curSquare = s;
    dir = d;
    done = false;
}

bool Projectile::isDone() {
    return done;
}

void Projectile::move() {
    Square* s = lvl->getSquareDir(curSquare, dir);
    // Only travel along floor squares
    if(!s->type() != SQUARE_FLOOR) {
        done = true;
        return;
    }
    else {
        // Kill an enemy when moving onto its square
        if(s->getEnemy() != 0) {
            lvl->killEnemy(s->getEnemy());
            s->setEnemy(0);
        }

        // Move onto the square
        curSquare->setProjectile(0);
        s->setProjectile(this);
        curSquare = s;
    }
}
