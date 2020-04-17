#ifndef georgebullet_h
#define georgebullet_h

#include "projectile.h"

class GeorgeBullet : public Projectile {
public:
  BeorgeBullet();
  GeorgeBullet(Level* l, Square* s, Direction d);
  char token();
private:
  Level* lvl;
  Square* curSquare;
  Direction dir;
};

#endif
