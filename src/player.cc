#include "player.h"

Player::Player() {}

Player::Player(World w) {
    world = w;
}

void Player::act(Action a) {

}

void Player::move(Direction dir) {
    // Get the square in the intended new position
    Square* s = curLvl.getSquareDir(curSquare, dir);
    // Don't do anything if there is no such square
    if(s == NULL) return; //TODO: Shouldn't happen?

    // Touching enemies is not allowed
    if(s->getEnemy() != NULL) {
        game->gameOver = true;
        return;
    }
    // Touching doors makes you go to a new room
    else if(s->type() == SQUARE_DOOR) {

    }

    // Move onto new floor square
    else if(s->type() == SQUARE_FLOOR){
        curSquare->setPlayer(NULL);
        s->setPlayer(this);
        curSquare = s;
    }

}
