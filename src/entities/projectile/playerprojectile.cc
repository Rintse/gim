#include "entities/projectiles/playerprojectile.h"
#include "world/squares/square.h"
#include "world/level.h"

PlayerProjectile::PlayerProjectile() {}

PlayerProjectile::PlayerProjectile(Level* l, EmptySquare* s, Direction d) : Projectile(l,s,d) {}

char PlayerProjectile::token(){
  return 'o';
}
