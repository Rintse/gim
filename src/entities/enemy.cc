#include "entities/enemy.h"
#include "world/level.h"

Enemy::Enemy() {}

Enemy::Enemy(Level* l, Square* s) {
    lvl = l;
    curSquare = s;
}

int Enemy::act() {
    return move(pathfind.getNextStep(curSquare));
}

Square* Enemy::getCurSquare() {
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
    // Two enemies may not occupy the same square
    if(s->getEnemy() != 0) return 0;
    // If you touch a projectile, you die
    if(s->getProjectile() != 0) return -1;
    // If you touch the player, he takes damage, you die
    if(s->getPlayer() != 0) {
        s->getPlayer()->takeDamage();
        return -1;
    }
    // Move onto new floor square
    else if(s->type() == SQUARE_FLOOR){
        curSquare->setEnemy(0);
        s->setEnemy(this);
        curSquare = s;
        facing = dir;
    }
    return 0;
}
