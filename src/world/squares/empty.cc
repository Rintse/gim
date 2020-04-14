#include "world/squares/empty.h"

EmptySquare::EmptySquare() {}
EmptySquare::~EmptySquare() {}

int EmptySquare::walkAgainst(directions dir) {
    return 0;
}

char EmptySquare::token() {
    return '-';
}
