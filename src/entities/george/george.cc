#include "entities/george/george.h"
#include "world/squares/square.h"
#include "world/level.h"

#include <iostream>

/*
BIG TODO LIJST

bullet ronde
barrier squares
george moet groter
sprites george en george health bar/getal
CODE DUPLICATION OMSCHRIJVEN
tgb ronde opschonen
fix destructor
*/

George::George() {}

George::George(Level* l, EmptySquare* s, int FPS) {
  lvl = l;
  curSquare = s;
  curRound = ROUND_TINYBABYGEORGES;
  frame = 0;
  health = HEALTH;
  setParts();
  cooldownFrames = FPS*COOLDOWN_SECONDS;
  roundFrames = FPS*ROUND_SECONDS;
  dir = DIR_RIGHT;
  fs = new FastRandom();
  lvlWidth = lvl->getWidth();
  lvlHeight = lvl->getHeight();
}

George::~George(){
  delete fs;
  //for(int i; i < N_PARTS; i++) {
  //  delete parts[i];
  //}
}

void George::setParts(){
  EmptySquare* tmp;
  parts[0] = dynamic_cast<GeorgePart*>(new GeorgeA(lvl, curSquare));
  curSquare->setGeorgepart(parts[0]);

  tmp = dynamic_cast<EmptySquare*>(lvl->getSquareDir(curSquare, DIR_RIGHT));
  parts[1] = dynamic_cast<GeorgePart*>(new GeorgeB(lvl, tmp));
  tmp->setGeorgepart(parts[1]);

  tmp = dynamic_cast<EmptySquare*>(lvl->getSquareDir(tmp, DIR_RIGHT));
  parts[2] = dynamic_cast<GeorgePart*>(new GeorgeC(lvl, tmp));
  tmp->setGeorgepart(parts[2]);

  tmp = dynamic_cast<EmptySquare*>(lvl->getSquareDir(curSquare, DIR_DOWN));
  parts[3] = dynamic_cast<GeorgePart*>(new GeorgeD(lvl, tmp));
  tmp->setGeorgepart(parts[3]);

  tmp = dynamic_cast<EmptySquare*>(lvl->getSquareDir(tmp, DIR_RIGHT));
  parts[4] = dynamic_cast<GeorgePart*>(new GeorgeE(lvl, tmp));
  tmp->setGeorgepart(parts[4]);

  tmp = dynamic_cast<EmptySquare*>(lvl->getSquareDir(tmp, DIR_RIGHT));
  parts[5] = dynamic_cast<GeorgePart*>(new GeorgeF(lvl, tmp));
  tmp->setGeorgepart(parts[5]);
}

void George::inputToParts() {
  int start = 0, end = N_PARTS, inc = 1;
  if(input.act < ACTION_NONE) {
    dir = static_cast<Direction>(input.act);
  }

  if(input.act == ACTION_MOVERIGHT) {
    start = N_PARTS-1;
    end = -1;
    inc = -1;
  }

  for(int i = start; i != end; i += inc) {
    parts[i]->act(input);
  }
  curSquare = parts[0]->getSquare();
}

void George::act() {
  input.act = ACTION_NONE;
  input.fired = false;

  curRound = ROUND_LASERS;
  dynamic_cast<GeorgeGun*>(parts[3])->setRound(curRound);
  dynamic_cast<GeorgeGun*>(parts[5])->setRound(curRound);

  attackBullets();
  //attackLasers();
  //attackTinyGeorges();

  // attack round has ended, George is in cooldown
  /*
  if(curRound == ROUND_TINYBABYGEORGES && lvl->noEnemies()){
    //door naar volgende ronde
  }

  if(frame > roundFrames) {
    frame = (frame + 1) % (int)(roundFrames + cooldownFrames);
  }

  else {
    if(frame == 0 ){ // start of new attack round
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
  input.act = followPlayer();
  return;
}

void George::attackLasers() {
  input.fired = true;

  if(dir == DIR_RIGHT) {
    if(lvl->getSquareDir(parts[5]->getSquare(), dir)->type() == SQUARE_FLOOR) {
      input.act = ACTION_MOVERIGHT;
    }
    else {
      input.act = ACTION_MOVELEFT;
    }
  }

  else if(dir == DIR_LEFT) {
    if(lvl->getSquareDir(parts[0]->getSquare(), dir)->type() == SQUARE_FLOOR) {
      input.act = ACTION_MOVELEFT;
    }
    else {
      input.act = ACTION_MOVERIGHT;
    }
  }
}

void George::attackTinyGeorges() {
  input.fired = false;
  input.act = avoidPlayer();

  if(frame == 0) {
    spawnGeorges();
  }

  return;
}

void George::spawnGeorges() {
  int randX = 0, randY = 0;
  Square* tmp;

  for(int i = 0; i < N_TINYBABYGEORGES; i++){
    tmp = lvl->getSquare(randX, randY);

    while(tmp->type() != SQUARE_FLOOR ||
          (tmp->type() == SQUARE_FLOOR &&
          (dynamic_cast<EmptySquare*>(tmp)->getEnemy() != 0 ||
          dynamic_cast<EmptySquare*>(tmp)->getPlayer() != 0))) {
      randX = fs->getLong() % (lvlWidth-2) + 1;
      randY = fs->getLong() % (lvlHeight-2) + 1;
      tmp = lvl->getSquare(randX, randY);
    }

    lvl->spawnEnemy(tmp);
  }
}

Action George::avoidPlayer() {
  int playerX = lvl->getPlayer()->getSquare()->getX();
  int georgeLeft = curSquare->getX();
  int georgeRight = georgeLeft + WIDTH-1;

  // player is in front of george
  if (playerX >= georgeLeft && playerX <= georgeRight) {
    if(lvl->getSquareDir(parts[5]->getSquare(), dir)->type() != SQUARE_FLOOR) {
      return ACTION_MOVELEFT;
    }
    else if (lvl->getSquareDir(parts[0]->getSquare(), dir)->type() != SQUARE_FLOOR) {
      return ACTION_MOVERIGHT;
    }

    return static_cast<Action>(dir);
  }

  // if george against wall
  if(lvl->getSquareDir(parts[5]->getSquare(), dir)->type() != SQUARE_FLOOR ||
     lvl->getSquareDir(parts[0]->getSquare(), dir)->type() != SQUARE_FLOOR) {
    return ACTION_NONE;
  }

  // player is left of george
  if (playerX <= georgeLeft) {
    return ACTION_MOVERIGHT;
  }

  // player is right of george
  return ACTION_MOVELEFT;
}

Action George::followPlayer() {
  int playerX = lvl->getPlayer()->getSquare()->getX();
  int georgeLeft = curSquare->getX();
  int georgeRight = georgeLeft + WIDTH-1;

  // player is left of george
  if (playerX < georgeLeft) {
    return ACTION_MOVELEFT;
  }

  // player is right of george
  if (playerX > georgeRight) {
    return ACTION_MOVERIGHT;
  }

  if (playerX == georgeLeft || playerX == georgeRight){
    return ACTION_NONE;
  }

  // player is in front of george
  if (playerX > georgeLeft && playerX < georgeRight) {
    if(lvl->getSquareDir(parts[5]->getSquare(), dir)->type() != SQUARE_FLOOR) {
      return ACTION_MOVELEFT;
    }
    else if (lvl->getSquareDir(parts[0]->getSquare(), dir)->type() != SQUARE_FLOOR) {
      return ACTION_MOVERIGHT;
    }

    return (georgeLeft - playerX) >= (playerX - georgeRight)?
            ACTION_MOVERIGHT : ACTION_MOVELEFT;
  }
  return ACTION_NONE;
}

bool George::takehit() {
  health--;
  return health == 0;
}

int George::takeHP() {
  return health;
}
