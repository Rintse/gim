#ifndef empty_h
#define empty_h

#include "world/squares/square.h"

class EmptySquare : public Square {
    public:
        EmptySquare();
        ~EmptySquare();

        void walkAgainst(directions dir);

    private:
};

#endif
