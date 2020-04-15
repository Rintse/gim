#ifndef door_h
#define door_h

#include "world/squares/square.h"

class DoorSquare : public Square {
    public:
        DoorSquare(int _x, int _y);
        ~DoorSquare();

        SquareType type();
        char token();

    private:
};

#endif
