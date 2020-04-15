#include "player.h"
#include "world/squares/square.h"
#include "world/level.h"
#include <iostream>

Player::Player() {}

Player::Player(Level* l) {
    curLvl = l;
    facing = DIR_UP;
}

void Player::setSquare(Square* s) {
    curSquare = s;
}

void Player::shoot() {
    Square* s = curLvl->getSquareDir(curSquare, facing);
    if(s->type() != SQUARE_FLOOR) {
        return;
    }
    else {
        curLvl->newProjectile(s, facing);
    }
}

void Player::act(Action a) {
    switch (a) {
        case ACTION_MOVEUP: move(DIR_UP); break;
        case ACTION_MOVEDOWN: move(DIR_DOWN); break;
        case ACTION_MOVERIGHT: move(DIR_RIGHT); break;
        case ACTION_MOVELEFT: move(DIR_LEFT); break;
        case ACTION_SHOOT: shoot(); break;
        default: return;
    }
}

char Player::token() {
    switch (facing) {
        case DIR_UP: return '^';
        case DIR_LEFT: return '<';
        case DIR_DOWN: return 'v';
        case DIR_RIGHT: return '>';
        default: return '0';
    }
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
        facing = dir;
    }

}
