#include "world/squares/wall.h"

WallSquare::WallSquare() {}
WallSquare::~WallSquare() {}

int WallSquare::walkAgainst(Direction dir) {
    return 0;
}

char WallSquare::token() {
    return '#';
}
