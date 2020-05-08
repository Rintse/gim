#include "entities/george/georgenogun.h"
#include "world/squares/square.h"
#include "world/level.h"

GeorgeNoGun::GeorgeNoGun() {}

GeorgeNoGun::GeorgeNoGun(Level* l, EmptySquare* s, char t) : GeorgePart (l,s,t) {}

void GeorgeNoGun::act(Input i) {
  switch (i.act) {
      case ACTION_MOVEUP: move(DIR_UP); break;
      case ACTION_MOVEDOWN: move(DIR_DOWN); break;
      case ACTION_MOVERIGHT: move(DIR_RIGHT); break;
      case ACTION_MOVELEFT: move(DIR_LEFT); break;
      default: break;
  }
}
