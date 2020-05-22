#include "world/squares/empty.h"

EmptySquare::EmptySquare(int x, int y) : Square(x,y) {
    player = 0;
    projectile = 0;
    enemy = 0;
    georgepart = 0;
    pu = 0;
    barrier = false;
}

EmptySquare::EmptySquare(int x, int y, bool b) : Square(x,y) {
    player = 0;
    projectile = 0;
    enemy = 0;
    georgepart = 0;
    pu = 0;
    barrier = b;
}


EmptySquare::~EmptySquare() {
    if(pu) delete pu;
}

SquareType EmptySquare::type() {
    return SQUARE_FLOOR;
}

char EmptySquare::token() {
    if(player != 0) { return player->token(); }
    else if(enemy != 0) { return enemy->token(); }
    else if(georgepart != 0) { return georgepart->token(); }
    else if(pu != 0) { return pu->token(); }
    else if(projectile != 0) { return projectile->token(); }
    else return ' ';
}

// Getters
Player* EmptySquare::getPlayer() { return player; }
Projectile* EmptySquare::getProjectile() { return projectile; }
Enemy* EmptySquare::getEnemy() { return enemy; }
GeorgePart* EmptySquare::getGeorgepart() { return georgepart; }
Powerup* EmptySquare::getPowerup() { return pu; }
bool EmptySquare::getBarrier() {return barrier; }

// Setters
void EmptySquare::setPlayer(Player* p) { player = p; }
void EmptySquare::setProjectile(Projectile *p) { projectile = p; }
void EmptySquare::setEnemy(Enemy* e) { enemy = e; }
void EmptySquare::setGeorgepart(GeorgePart* g) { georgepart = g; }
void EmptySquare::setPowerup(Powerup* p) { pu = p; }
