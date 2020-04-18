#include "entities/george.h"
#include "world/squares/square.h"
#include "world/level.h"

George::George() {}

George::George(Level* l, Square* s) {
  lvl = l;
  curSquare = s;
  curRound = 2;
  frame = 0;
}

void George::act() {
  // attack round has ended, George is in cooldown
  if(frame > ROUND_FRAMES) {
    frame = (frame + 1) % (int)(ROUND_FRAMES + COOLDOWN_FRAMES);
  }

  else {

    if(frame == 0){ // start of new attack round
      curRound = (curRound + 1) % 3;
    }

    // each round has a different attack type
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
    }
  }

  frame++;
}

void George::attackBullets() {
  // schiet bullets vanaf de 2 gun squares
  // volg de player een beetje op de x as
  return;
}

void George::attackLasers() {
  // ga heen en weer
 // vuur continue 1/2 lasers
  return;
}

void George::attackTinyGeorges() {
  // willekeurige beweging op de x as?
  // spawn tiny baby georges op willekeurige plekken in het level
  return;
}
