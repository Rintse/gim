#include "entities/george/georgepart.h"
#include "world/squares/square.h"
#include "world/level.h"

#include <iostream>

GeorgePart::GeorgePart() {}

GeorgePart::GeorgePart(Level* l, EmptySquare* s) {
  lvl = l;
  curSquare = s;
}

EmptySquare* GeorgePart::getSquare() {
  return curSquare;
}

void GeorgePart::move(Direction dir) {
  // Get the square in the intended new position
  Square* s = lvl->getSquareDir(curSquare, dir);
  if(s == NULL) { return; }

  // Move onto new floor square
  else if(s->type() == SQUARE_FLOOR){
      curSquare->setGeorgepart(0);
      dynamic_cast<EmptySquare*>(s)->setGeorgepart(this);
      curSquare = dynamic_cast<EmptySquare*>(s);
  }
}
