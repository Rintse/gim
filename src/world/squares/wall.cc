#include "world/squares/wall.h"

WallSquare::WallSquare(int x, int y) : Square(x,y) {}

WallSquare::~WallSquare() {

}

SquareType WallSquare::type() {
    return SQUARE_WALL;
}

char WallSquare::token() {
    return '#';
}
