#ifndef wall_h
#define wall_h

#include "world/squares/square.h"

class WallSquare : public Square {
    public:
        WallSquare(int _x, int _y);
        ~WallSquare();

        SquareType type();
        char token();

    private:
};

#endif
