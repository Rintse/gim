#ifndef georgelaser_h
#define georgelaser_h

#include "projectile.h"

class GeorgeLaser : public Projectile {
public:
  GeorgeLaser();
  GeorgeLaser(Level* l, Square* s, Direction d);
  char token();
private:
};

#endif
