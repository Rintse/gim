#include "projectile.h"

Enemy::Enemy() {}

Enemy::Enemy(Level l, Square s) {
    lvl = l;
    curSquare = s;
}

Action Enemy::decideMove() {
    return ACTION_NONE;
}

void Enemy::act() {
    switch(nextMove) {
        default: return;
    }

    nextMove = ACTION_NONE;
}
