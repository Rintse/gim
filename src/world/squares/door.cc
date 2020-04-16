#include "world/squares/door.h"

DoorSquare::DoorSquare(int x, int y, Direction d) : Square(x,y) {
    dir = d;
}
DoorSquare::~DoorSquare() {}

SquareType DoorSquare::type() {
    return SQUARE_DOOR;
}

Direction DoorSquare::getDir() {
    return dir;
}

char DoorSquare::token() {
    return ' ';
}
