#ifndef empty_h
#define empty_h

#include "world/squares/square.h"

class EmptySquare : public Square {
    public:
        EmptySquare(int _x, int _y);
        ~EmptySquare();

        SquareType type();
        char token();

    private:
};

#endif
