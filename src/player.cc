#include "player.h"
#include "world/squares/square.h"
#include "world/level.h"

Player::Player() {}

Player::Player(Level* l) {
    curLvl = l;
}

void Player::act(Action a) {

}

void Player::move(Direction dir) {
    // Get the square in the intended new position
    Square* s = curLvl->getSquareDir(curSquare, dir);
    // Don't do anything if there is no such square
    if(s == 0) return; //TODO: Shouldn't happen?

    // Touching enemies is not allowed
    if(s->getEnemy() != 0) {
        //TODO:gameover
        return;
    }
    // Touching doors makes you go to a new room
    else if(s->type() == SQUARE_DOOR) {

    }

    // Move onto new floor square
    else if(s->type() == SQUARE_FLOOR){
        curSquare->setPlayer(0);
        s->setPlayer(this);
        curSquare = s;
    }

}
