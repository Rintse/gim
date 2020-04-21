#include "entities/george/georgegun.h"
#include "world/squares/square.h"
#include "world/level.h"

GeorgeGun::GeorgeGun() {}

GeorgeGun::GeorgeGun(Level* l, EmptySquare* s) : GeorgePart (l,s) {
  curRound = ROUND_BULLETS;
}

void GeorgeGun::act(Input i) {
  if(i.act != ACTION_NONE) {
    switch (i.act) {
        case ACTION_MOVEUP: dir = DIR_UP; break;
        case ACTION_MOVEDOWN: dir = DIR_DOWN; break;
        case ACTION_MOVERIGHT: dir = DIR_RIGHT; break;
        case ACTION_MOVELEFT: dir = DIR_LEFT; break;
        default: break;
    }
    move(dir);
  }

  if(i.fired){
    if(curRound == ROUND_BULLETS){
      shootBullet();
    }
    else if(curRound == ROUND_LASERS){
      shootLaser();
    }
  }
}

void GeorgeGun::shootBullet(){
  if(curSquare->type() != SQUARE_FLOOR ) {
      return;
  }
  else {
    Projectile* tmp = dynamic_cast<Projectile*>(
        new GeorgeBullet(lvl, dynamic_cast<EmptySquare*>(curSquare), DIR_DOWN));
    lvl->newProjectile(tmp);
  }
}

void GeorgeGun::shootLaser(){
  if(curSquare->type() != SQUARE_FLOOR) {
      return;
  }
  else {
    Projectile* tmp = dynamic_cast<Projectile*>(
        new GeorgeLaser(lvl, dynamic_cast<EmptySquare*>(curSquare), DIR_DOWN, dir));
    lvl->newProjectile(tmp);
  }
}

void GeorgeGun::setRound(Round round){
  curRound = round;
}
