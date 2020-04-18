#include "entities/georgegun.h"
#include "world/squares/square.h"
#include "world/level.h"

GeorgeGun::GeorgeGun() {}

GeorgeGun::GeorgeGun(Level* l, Square* s) : GeorgePart (l,s) {}

void GeorgeGun::act(int curRound, Direction dir) {
  return;
}

void GeorgeGun::shootBullet(){
  if(curSquare->type() != SQUARE_FLOOR ) {
      return;
  }
  else {
      lvl->newGeorgeBullet(curSquare, DIR_DOWN);
  }
}

void GeorgeGun::shootLaser(){
  if(curSquare->type() != SQUARE_FLOOR) {
      return;
  }
  else {
      lvl->newGeorgeLaser(curSquare, DIR_DOWN);
  }
}
