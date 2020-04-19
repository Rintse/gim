#include "entities/projectiles/georgelaser.h"
#include "world/squares/square.h"
#include "world/level.h"

GeorgeLaser::GeorgeLaser() {}

GeorgeLaser::GeorgeLaser(Level* l, EmptySquare* s, Direction d) : Projectile(l,s,d) {}

char GeorgeLaser::token(){
  return '|';
}
