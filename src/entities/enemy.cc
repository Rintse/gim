#include "entities/enemy.h"
#include "world/level.h"

Enemy::Enemy() {}

Enemy::Enemy(Level* l, EmptySquare* s) : pathfind(l) {
    lvl = l;
    curSquare = s;
    lockout = 0;
}

int Enemy::act() {
    if(lockout < LOCKOUTFRAMES) {
        lockout++;
        return 0;
    }
    lockout = 0;

    switch (pathfind.getNextStep(curSquare)) {
        case ACTION_MOVEUP: return move(DIR_UP); break;
        case ACTION_MOVEDOWN: return move(DIR_DOWN); break;
        case ACTION_MOVERIGHT: return move(DIR_RIGHT); break;
        case ACTION_MOVELEFT: return move(DIR_LEFT); break;
        default: return 0;
    }
}

EmptySquare* Enemy::getSquare() {
    return curSquare;
}

char Enemy::token() {
    switch (facing) {
        case DIR_UP: return 'w';
        case DIR_LEFT: return 'a';
        case DIR_DOWN: return 's';
        case DIR_RIGHT: return 'd';
        default: return '0';
    }
}

int Enemy::move(Direction dir) {
    // Get the square in the intended new position
    Square* s = lvl->getSquareDir(curSquare, dir);
    if(s == NULL) return 0;
    // Move onto new floor square
    else if(s->type() == SQUARE_FLOOR){
        EmptySquare* es = dynamic_cast<EmptySquare*>(s);
        // Two enemies may not occupy the same square
        if(es->getEnemy() != 0) return 0;
        // If you touch a projectile, you die
        if(es->getProjectile() != 0) return -1;
        // If you touch the player, he takes damage, you die
        if(es->getPlayer() != 0) {
            es->getPlayer()->takeDamage();
            return -1;
        }
        curSquare->setEnemy(0);
        es->setEnemy(this);
        curSquare = es;
        facing = dir;
    }
    return 0;
}
