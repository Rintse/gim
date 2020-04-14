#include "world/squares/wall.h"

WallSquare::WallSquare() {}
WallSquare::~WallSquare() {}

int WallSquare::walkAgainst(directions dir) {
    return 0;
}

char WallSquare::token() {
    return '#';
}
