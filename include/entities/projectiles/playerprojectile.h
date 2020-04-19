#ifndef playerprojectile_h
#define playerprojectile_h

#include "projectile.h"

class PlayerProjectile : public Projectile {
public:
  PlayerProjectile();
  PlayerProjectile(Level* l, EmptySquare* s, Direction d);
  char token();
};

#endif
