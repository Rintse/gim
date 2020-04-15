#include "world/squares/empty.h"

EmptySquare::EmptySquare(int x, int y) : Square(x,y) {}
EmptySquare::~EmptySquare() {}

SquareType EmptySquare::type() {
    return SQUARE_FLOOR;
}

char EmptySquare::token() {
    return ' ';
}
