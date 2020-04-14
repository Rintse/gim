#ifndef wall_h
#define wall_h

#include "world/squares/square.h"

class WallSquare : public Square {
    public:
        WallSquare();
        ~WallSquare();

        int walkAgainst(directions dir);
        char token();

    private:
};

#endif
