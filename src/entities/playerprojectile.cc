#include "entities/playerprojectile.h"
#include "world/squares/square.h"
#include "world/level.h"

PlayerProjectile::PlayerProjectile() {}

PlayerProjectile::PlayerProjectile(Level* l, Square* s, Direction d) {
    lvl = l;
    curSquare = s;
    dir = d;
}

char PlayerProjectile::token(){
  return 'o';
}
