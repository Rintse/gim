#ifndef square_h
#define square_h

#include "tools/directions.h"
//TODO : verplaatsen includes
#include "entities/player.h"
#include "entities/enemy.h"
#include "entities/george/georgepart.h"
#include "entities/projectiles/projectile.h"

enum SquareType {
    SQUARE_FLOOR, SQUARE_DOOR, SQUARE_WALL
};

class Square {
    public:
        Square(int _x, int _y);
        virtual ~Square();

        virtual char token() = 0;
        virtual SquareType type() = 0;
        int getX();
        int getY();

    protected:
        int x,y;
};

#endif
