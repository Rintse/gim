#ifndef square_h
#define square_h

#include "directions.h"

class Square {
    public:
        Square() {}
        virtual ~Square() {}
        virtual int walkAgainst(Direction dir) = 0;
        virtual char token() = 0;
    private:

};

#endif
