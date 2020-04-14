#ifndef empty_h
#define empty_h

#include "world/squares/square.h"

class EmptySquare : public Square {
    public:
        EmptySquare();
        ~EmptySquare();

        int walkAgainst(Direction dir);
        char token();

    private:
};

#endif
