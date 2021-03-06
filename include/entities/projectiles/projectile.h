#ifndef projectile_h
#define projectile_h

#include "tools/directions.h"

class Level;
class EmptySquare;

class Projectile {
public:
  Projectile();
  Projectile(Level* l, EmptySquare* s, Direction d);
  virtual ~Projectile();
  int move();
  EmptySquare* getSquare();
  virtual char token() = 0;
  Direction getDirection();

protected:
  Level* lvl;
  EmptySquare* curSquare;
  Direction dir;
  int speed;
};

#endif
