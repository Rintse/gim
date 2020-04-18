#include "entities/george/george.h"
#include "world/squares/square.h"
#include "world/level.h"

George::George() {}

George::George(Level* l, Square* s, int FPS) {
  lvl = l;
  curSquare = s;
  curRound = ROUND_TINYBABYGEORGES;
  frame = 0;
  health = 100;
  setParts();
  cooldownFrames = FPS*COOLDOWN_SECONDS;
  roundFrames = FPS*ROUND_SECONDS;
  dir = DIR_RIGHT;
}

void George::setParts(){
  Square* tmp;
  parts[0] = dynamic_cast<GeorgePart*>(new GeorgeA(lvl, curSquare));
  curSquare->setGeorgepart(parts[0]);

  tmp = lvl->getSquareDir(curSquare, DIR_RIGHT);
  parts[1] = dynamic_cast<GeorgePart*>(new GeorgeB(lvl, tmp));
  tmp->setGeorgepart(parts[1]);

  tmp = lvl->getSquareDir(tmp, DIR_RIGHT);
  parts[2] = dynamic_cast<GeorgePart*>(new GeorgeC(lvl, tmp));
  tmp->setGeorgepart(parts[2]);

  tmp = lvl->getSquareDir(curSquare, DIR_DOWN);
  parts[3] = dynamic_cast<GeorgePart*>(new GeorgeD(lvl, tmp));
  tmp->setGeorgepart(parts[3]);

  tmp = lvl->getSquareDir(tmp, DIR_RIGHT);
  parts[4] = dynamic_cast<GeorgePart*>(new GeorgeE(lvl, tmp));
  tmp->setGeorgepart(parts[4]);

  tmp = lvl->getSquareDir(tmp, DIR_RIGHT);
  parts[5] = dynamic_cast<GeorgePart*>(new GeorgeF(lvl, tmp));
  tmp->setGeorgepart(parts[5]);
}

void George::inputToParts() {
  for(int i = 0; i < N_PARTS; i++) {
    parts[i]->act(input);
  }
}

void George::act() {
  input.act = ACTION_NONE;
  input.fired = false;

  curRound = ROUND_LASERS;
  dynamic_cast<GeorgeGun*>(parts[3])->setRound(curRound);
  dynamic_cast<GeorgeGun*>(parts[5])->setRound(curRound);
  attackLasers();

  // attack round has ended, George is in cooldown
  /*if(frame > roundFrames) {
    frame = (frame + 1) % (int)(roundFrames + cooldownFrames);
  }

  else {
    if(frame == 0){ // start of new attack round
      curRound = static_cast<Round>(((int)curRound + 1) % 3);
      dynamic_cast<GeorgeGun*>(parts[3])->setRound(curRound);
      dynamic_cast<GeorgeGun*>(parts[5])->setRound(curRound);
    }

    // each round has a different attack type
    switch(curRound){
      case 0:
        attackBullets(i);
        break;
      case 1:
        attackLasers(i);
        break;
      case 2:
        attackTinyGeorges(i);
        break;
    }
  }*/

  inputToParts();
  frame++;
}

void George::attackBullets() {
  // schiet bullets vanaf de 2 gun squares
  // volg de player een beetje op de x as
  return;
}

void George::attackLasers() {
  input.fired = true;

  if(dir == DIR_LEFT) {
    if(lvl->getSquareDir(parts[0]->getSquare(), dir)->type() == SQUARE_FLOOR) {
      input.act = ACTION_MOVELEFT;
    }
    else {
      dir = DIR_RIGHT;
      input.act = ACTION_MOVERIGHT;
    }
  }

  else if(dir == DIR_RIGHT) {
    if(lvl->getSquareDir(parts[5]->getSquare(), dir)->type() == SQUARE_FLOOR) {
      input.act = ACTION_MOVERIGHT;
    }
    else {
      dir = DIR_LEFT;
      input.act = ACTION_MOVELEFT;
    }
  }
}

void George::attackTinyGeorges() {
  // willekeurige beweging op de x as?
  // spawn tiny baby georges op willekeurige plek
  return;
}
