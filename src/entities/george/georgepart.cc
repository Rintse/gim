#include "entities/george/georgepart.h"
#include "world/squares/square.h"
#include "world/level.h"

GeorgePart::GeorgePart() {}

GeorgePart::GeorgePart(Level* l, Square* s) {
  lvl = l;
  curSquare = s;
}
