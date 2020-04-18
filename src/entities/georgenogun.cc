#include "entities/georgenogun.h"
#include "world/squares/square.h"
#include "world/level.h"

GeorgeNoGun::GeorgeNoGun() {}

GeorgeNoGun::GeorgeNoGun(Level* l, Square* s) : GeorgePart (l,s) {}

void GeorgeNoGun::act(Direction dir) {
  return;
}
