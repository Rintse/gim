#include "projectile.h"
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
    std::cout << "projectile move?" << std::endl;
    Square* s = lvl->getSquareDir(curSquare, dir);
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

        std::cout << "actual move?" << std::endl;
        // Move onto the square
        curSquare->setProjectile(0);
        s->setProjectile(this);
        curSquare = s;
    }

    return 0;
}
