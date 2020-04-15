#include "world/squares/wall.h"

WallSquare::WallSquare(int _x, int _y) {
    player = projectile = enemy = NULL;
    x = X;
    y = Y;
}

WallSquare::~WallSquare() {

}

SquareType WallSquare::type() {
    return SQUARE_WALL;
}

char WallSquare::token() {
    return '#';
}
