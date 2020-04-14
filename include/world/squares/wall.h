#ifndef wall_h
#define wall_h

#include "world/squares/square.h"

class WallSquare : public Square {
    public:
        WallSquare();
        ~WallSquare();

        void walkAgainst(directions dir);

    private:
};

#endif
