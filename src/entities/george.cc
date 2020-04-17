#include "entities/george.h"
#include "world/squares/square.h"
#include "world/level.h"

George::George() {}

George::George(Level* l, Square* s) {
  lvl = l;
  curSquare = s;
  curRound = 0;
}

void George::act() {
  switch(curRound){
    case 0:
      attackBullets();
      break;
    case 1:
      attackLasers();
      break;
    case 2:
      attackTinyGeorges();
      break;
  } // kan dit zonder een switch wat mooier?

  curRound = curRound+1 % 3;
}

void George::attackBullets() {

  return;
}

void George::attackLasers() {
  return;
}

void George::attackTinyGeorges() {
  return;
}

void George::shootBullet(Square* s){
  if(s->type() != SQUARE_FLOOR) {
      return;
  }
  else {
      lvl->newProjectile(s, DIR_DOWN, false);
  }
}

void George::shootLaser(){
  return;
}
