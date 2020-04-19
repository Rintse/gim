#include "entities/projectiles/georgebullet.h"
#include "world/squares/square.h"
#include "world/level.h"

GeorgeBullet::GeorgeBullet() {}

GeorgeBullet::GeorgeBullet(Level* l, EmptySquare* s, Direction d) : Projectile(l,s,d) {}

char GeorgeBullet::token(){
  return 'x';
}
