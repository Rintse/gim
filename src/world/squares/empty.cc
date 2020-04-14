#include "world/squares/empty.h"

EmptySquare::EmptySquare() {}
EmptySquare::~EmptySquare() {}

int EmptySquare::walkAgainst(Direction dir) {
    return 0;
}

char EmptySquare::token() {
    return '-';
}
