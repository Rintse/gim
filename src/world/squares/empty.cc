#include "world/squares/empty.h"

EmptySquare::EmptySquare(int x, int y) : Square(x,y) {
    player = 0;
    projectile = 0;
    enemy = 0;
    georgepart = 0;
    heart = false;
}
EmptySquare::~EmptySquare() {}

SquareType EmptySquare::type() {
    return SQUARE_FLOOR;
}

bool EmptySquare::hasHeart() {
    return heart;
}

void EmptySquare::setHeart(bool h) {
    heart = h;
}

char EmptySquare::token() {
    if(getPlayer() != 0) { return getPlayer()->token(); }
    else if(getEnemy() != 0) { return getEnemy()->token(); }
    else if(getGeorgepart() != 0) { return getGeorgepart()->token(); }
    else if(heart) return 'L';
    else if(getProjectile() != 0) { return getProjectile()->token(); }
    else return ' ';
}

// Getters
Player* EmptySquare::getPlayer() { return player; }
Projectile* EmptySquare::getProjectile() { return projectile; }
Enemy* EmptySquare::getEnemy() { return enemy; }
GeorgePart* EmptySquare::getGeorgepart() { return georgepart; }

// Setters
void EmptySquare::setPlayer(Player* p) { player = p; }
void EmptySquare::setProjectile(Projectile *p) { projectile = p; }
void EmptySquare::setEnemy(Enemy* e) { enemy = e; }
void EmptySquare::setGeorgepart(GeorgePart* g) { georgepart = g; }
