#include "entities/george/george.h"
#include "world/squares/square.h"
#include "world/level.h"

#include <iostream>

/*
BIG TODO LIJST

george moet groter
sprites george
CODE DUPLICATION OMSCHRIJVEN
*/

George::George() {}

George::George(Level* l, EmptySquare* s, int FPS) {
  lvl = l;
  curSquare = s;
  curRound = ROUND_BULLETS;
  frame = 0;
  health = HEALTH;
  setParts();
  cooldownFrames = FPS*COOLDOWN_SECONDS;
  roundFrames = FPS*ROUND_SECONDS;
  dir = DIR_RIGHT;
  fs = new FastRandom();
  lvlWidth = lvl->getWidth();
  lvlHeight = lvl->getHeight();
  cooldown = false;
}

George::~George(){
  delete fs;
  for(int i = 0; i < N_PARTS; i++) {
    delete parts[i];
  }
}


void George::setParts(){
  char tokens[N_PARTS];
  for (int i = 0; i < N_PARTS; i++) {
    tokens[i] = '#';
  }

  EmptySquare* tmp = curSquare, *left = curSquare;

  for(int i = 0; i < N_PARTS; i++) {
    // GUNS
    if(i == N_PARTS-1 || i == N_PARTS - WIDTH) {
      parts[i] = dynamic_cast<GeorgePart*>(new GeorgeGun(lvl, tmp, tokens[i]));
      tmp->setGeorgepart(parts[i]);
    }
    // no guns
    else {
      parts[i] = dynamic_cast<GeorgePart*>(new GeorgeNoGun(lvl, tmp, tokens[i]));
      tmp->setGeorgepart(parts[i]);
    }

    // set next square
    if(i % WIDTH == WIDTH-1 && i != N_PARTS-1) {
      tmp = dynamic_cast<EmptySquare*>(lvl->getSquareDir(left, DIR_DOWN));
      left = tmp;
    }
    else {
      tmp = dynamic_cast<EmptySquare*>(lvl->getSquareDir(tmp, DIR_RIGHT));
    }
  }
}

void George::inputToParts() {
  int start = 0, end = N_PARTS, inc = 1;

  // random behaviour in ROUND_BULLETS and ROUND_TINYBABYGEORGES
  if (curRound != ROUND_LASERS && fs->getLong() % 2 == 0) {
    switch(fs->getLong() % 3) {
      case 0: input.act = ACTION_MOVELEFT;
      case 1: input.act = ACTION_MOVERIGHT;
      case 2: input.act = ACTION_NONE;
    }
  }
  // slow george down a bit...
  else if (curRound == ROUND_LASERS && frame % 2 == 1) {
    input.act = ACTION_NONE;
  }

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
  if(cooldown && frame >= cooldownFrames) {
    frame = 0;
    cooldown = false;
  }

  if(!cooldown) {
    // each round has a different attack type
    switch(curRound){
      case ROUND_BULLETS:
        attackBullets();
        break;
      case ROUND_LASERS:
        attackLasers();
        break;
      case ROUND_TINYBABYGEORGES:
        attackTinyGeorges();
        break;
    }
    cooldown = setRound();
  }

  inputToParts();
  frame++;
}

void George::attackBullets() {
  if (frame % BULLET_PAUSE == 0) {
    input.fired = true;
  }
  else {
    input.fired = false;
  }

  input.act = followPlayer();
  return;
}

void George::attackLasers() {
  input.fired = true;

  if(dir == DIR_RIGHT) {
    if(lvl->getSquareDir(parts[N_PARTS-1]->getSquare(), dir)->type() == SQUARE_FLOOR) {
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
    if(lvl->getSquareDir(parts[N_PARTS-1]->getSquare(), dir)->type() != SQUARE_FLOOR) {
      return ACTION_MOVELEFT;
    }
    else if (lvl->getSquareDir(parts[0]->getSquare(), dir)->type() != SQUARE_FLOOR) {
      return ACTION_MOVERIGHT;
    }

    return static_cast<Action>(dir);
  }

  // if george against wall
  if(lvl->getSquareDir(parts[N_PARTS-1]->getSquare(), dir)->type() != SQUARE_FLOOR ||
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
    if(lvl->getSquareDir(parts[N_PARTS-1]->getSquare(), dir)->type() != SQUARE_FLOOR) {
      return ACTION_MOVELEFT;
    }
    else if (lvl->getSquareDir(parts[0]->getSquare(), dir)->type() != SQUARE_FLOOR) {
      return ACTION_MOVERIGHT;
    }

    else if((georgeLeft - playerX) > (playerX - georgeRight)) {
      return ACTION_MOVELEFT;
    }

    else if ((georgeLeft - playerX) < (playerX - georgeRight)) {
      return ACTION_MOVERIGHT;
    }
  }

  return static_cast<Action>(dir);
}

bool George::takehit() {
  health--;
  return health == 0;
}

int George::getHP() {
  return health;
}

bool George::setRound() {
  switch(curRound){
    case ROUND_BULLETS:
    case ROUND_LASERS:
      if (frame >= roundFrames) {
        advanceRound();
        return true;
      }
      break;
    case ROUND_TINYBABYGEORGES:
      if (lvl->noEnemies()) {
        advanceRound();
        return true;
      }
      break;
    default: break;
  }
  return false;
}

void George::advanceRound() {
  frame = 0;
  input.act = ACTION_NONE;
  input.fired = false;
  curRound = static_cast<Round>(((int)curRound + 1) % 3);
  dynamic_cast<GeorgeGun*>(parts[N_PARTS-WIDTH])->setRound(curRound);
  dynamic_cast<GeorgeGun*>(parts[N_PARTS-1])->setRound(curRound);
}
