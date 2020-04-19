#include "world/squares/square.h"

Square::Square(int _x, int _y) {
    x = _x;
    y = _y;
}
Square::~Square() {}

// Getters
int Square::getX() { return x; }
int Square::getY() { return y; }
