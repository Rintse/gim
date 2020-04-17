#ifndef projectile_h
#define projectile_h

#include "tools/directions.h"

class Level;
class Square;

class Projectile {
public:
  Projectile();
  Projectile(Level* l, Square* s, Direction d);
  int move();
  Square* getCurSquare();
  virtual char token() = 0;

protected:
  Level* lvl;
  Square* curSquare;
  Direction dir;
};

#endif
