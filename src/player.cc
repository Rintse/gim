#include "player.h"

Player::Player() {}

Player::Player(World w) {
    world = w;
}

void Player::move(Direction dir) {
    // Get intended new position
    int ty = y, tx = x;
    switch (dir) {
        case UP: ty++; break;
        case LEFT: tx++; break;
        case DOWN: ty--; break;
        case RIGHT: tx--; break;
    }

    // Get the square in this position
    Square* s = curLvl.getSquare(tx, ty);
    // Don't do anything if there is no such square
    if(s == NULL) return;

    // Signal the square that we moved against it (and from what direction)
    int movement = s->walkAgainst(dir);
    // If the block allows us to move this way, move
    if(movement != 0) {
        x = tx;
        y = ty;
    }
}
