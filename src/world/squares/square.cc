#include "world/squares/square.h"

Square::Square(int _x, int _y) {
    player = 0;
    projectile = 0;
    enemy = 0;
    x = _x;
    y = _y;
}
Square::~Square() {}

// Getters
int Square::getX() { return x; }
int Square::getY() { return y; }
Player* Square::getPlayer() { return player; }
Projectile* Square::getProjectile() { return projectile; }
Enemy* Square::getEnemy() { return enemy; }

// Setters
void Square::setPlayer(Player* p) { player = p; }
void Square::setProjectile(Projectile *p) { projectile = p; }
void Square::setEnemy(Enemy* e) { enemy = e; }
