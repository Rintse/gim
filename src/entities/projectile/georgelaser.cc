#include "entities/projectiles/georgelaser.h"
#include "world/squares/square.h"
#include "world/level.h"

GeorgeLaser::GeorgeLaser() {}

GeorgeLaser::GeorgeLaser(Level* l, EmptySquare* s, Direction d, Direction g) : Projectile(l,s,d) {
    speed = 1;
    gDir = g;
}

char GeorgeLaser::token(){
  return gDir == DIR_RIGHT ? '/' : '|';
}
