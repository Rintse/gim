#ifndef georgebullet_h
#define georgebullet_h

#include "projectile.h"

class GeorgeBullet : public Projectile {
public:
  GeorgeBullet();
  GeorgeBullet(Level* l, EmptySquare* s, Direction d);
  char token();
private:
};

#endif
