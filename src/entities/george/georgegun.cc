#include "entities/george/georgegun.h"
#include "world/squares/square.h"
#include "world/level.h"
#include <iostream>

GeorgeGun::GeorgeGun() {}

GeorgeGun::GeorgeGun(Level* l, Square* s) : GeorgePart (l,s) {
  curRound = ROUND_BULLETS;
}

void GeorgeGun::act(Input i) {
  if(i.fired){
    if(curRound == ROUND_BULLETS){
      shootBullet();
    }
    else if(curRound == ROUND_LASERS){
      shootLaser();
    }
  }

  switch (i.act) {
      case ACTION_MOVEUP: move(DIR_UP); break;
      case ACTION_MOVEDOWN: move(DIR_DOWN); break;
      case ACTION_MOVERIGHT: move(DIR_RIGHT); break;
      case ACTION_MOVELEFT: move(DIR_LEFT); break;
      default: break;
  }
}

void GeorgeGun::shootBullet(){
  if(curSquare->type() != SQUARE_FLOOR ) {
      return;
  }
  else {
      //lvl->newGeorgeBullet(curSquare, DIR_DOWN);
  }
}

void GeorgeGun::shootLaser(){
  if(curSquare->type() != SQUARE_FLOOR) {
      return;
  }
  else {
      //lvl->newGeorgeLaser(curSquare, DIR_DOWN);
  }
}

void GeorgeGun::setRound(Round round){
  curRound = round;
}
