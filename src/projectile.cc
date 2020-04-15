#include "projectile.h"

Projectile::Projectile() {}

Projectile::Projectile(Level l, Square s, Direction d) {
    lvl = l;
    curSquare = s;
    dir = d;
    isDone = false;
}

Projectile::isDone() {
    return isDone;
}

Projectile::move() {
    Square* s = lvl->getSquareDir(curSquare, dir);
    // Only travel along floor squares
    if(!s->type() != SQUARE_FLOOR) {
        isDone = true;
        return;
    }
    else {
        // Kill an enemy when moving onto its square
        if(s->getEnemy() != NULL) {
            lvl->kill(s->getEnemy());
            s->setEnemy(NULL);
        }

        // Move onto the square
        curSquare->setProjectile(NULL);
        s->setProjectile(this);
        curSquare = s;
    }
}
