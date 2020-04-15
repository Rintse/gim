#include "world/squares/door.h"

DoorSquare::DoorSquare(int x, int y) : Square(x,y) {}
DoorSquare::~DoorSquare() {}

SquareType DoorSquare::type() {
    return SQUARE_DOOR;
}

char DoorSquare::token() {
    return '-';
}
