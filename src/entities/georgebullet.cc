#include "entities/georgebullet.h"
#include "world/squares/square.h"
#include "world/level.h"

GeorgeBullet::GeorgeBullet() {}

GeorgeBullet::GeorgeBullet(Level* l, Square* s, Direction d) {
    lvl = l;
    curSquare = s;
    dir = d;
    player = p;
}

GeorgeBullet::token(){
  return 'o';
}
