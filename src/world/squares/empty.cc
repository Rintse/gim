#include "world/squares/empty.h"

EmptySquare::EmptySquare(int _x, int _y) {
    player = projectile = enemy = NULL;
    x = _x;
    y = _y;
}
EmptySquare::~EmptySquare() {}

SquareType EmptySquare::type() {
    return SQUARE_FLOOR;
}

char EmptySquare::token() {
    return '-';
}
