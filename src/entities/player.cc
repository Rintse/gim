#include "entities/player.h"
#include "world/squares/square.h"
#include "world/level.h"
#include "tools/key_input.h"
#include "entities/projectiles/playerprojectile.h"
#include <iostream>

Player::Player() {}

Player::Player(Level* l) {
    curLvl = l;
    facing = DIR_UP;
    health = 2;
    curSLO = curMLO = -1;
    moveLockout = SLOW_MLO;
    shootLockout = START_SLO;
}

void Player::decreaseSLO() {
    if(shootLockout > 1) {
        shootLockout -= 4;
    }
}

void Player::setSquare(EmptySquare* s) {
    curSquare = s;
}

void Player::setLevel(Level* l) {
    curLvl = l;
}

void Player::takeDamage() {
    if(--health < 1) { curLvl->signalGameOver(); }
}

void Player::increaseHP() {
    if(health < 9) health++;
}

int Player::getHP() {
    return health;
}

void Player::shoot() {
    if(curSLO >= 0) return;
    else curSLO = shootLockout;

    Square* s = curLvl->getSquareDir(curSquare, facing);
    if(s->type() != SQUARE_FLOOR) {
        return;
    }
    else {
        Projectile* tmp = dynamic_cast<Projectile*>(
            new PlayerProjectile(curLvl, dynamic_cast<EmptySquare*>(s), facing));
        curLvl->newProjectile(tmp);
    }
}

void Player::advanceLockouts() {
    if(curMLO >= 0) curMLO--; // Movement
    if(curSLO >= 0) curSLO--; // Firing
}

void Player::act(Input in) {
    advanceLockouts();

    if(in.sprint) { moveLockout = FAST_MLO; }
    else { moveLockout = SLOW_MLO; }

    switch (in.act) {
        case ACTION_MOVEUP: move(DIR_UP); break;
        case ACTION_MOVEDOWN: move(DIR_DOWN); break;
        case ACTION_MOVERIGHT: move(DIR_RIGHT); break;
        case ACTION_MOVELEFT: move(DIR_LEFT); break;
        default: break;
    }

    if(in.fired) {
        shoot();
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


EmptySquare* Player::getSquare() {
    return curSquare;
}


void Player::move(Direction dir) {
    if(curMLO >= 0) return;
    else curMLO = moveLockout;

    // Get the square in the intended new position
    Square* s = curLvl->getSquareDir(curSquare, dir);
    if(s == NULL) { return; }
    // Touching doors makes you go to a new room
    else if(s->type() == SQUARE_DOOR) {
        Direction dir = dynamic_cast<DoorSquare*>(s)->getDir();
        curLvl->switchLevel(dir);
        facing = dir;
    }
    // Move onto new floor square
    else if(s->type() == SQUARE_FLOOR){
        if(!static_cast<EmptySquare*>(s)->getBarrier()) {
          EmptySquare* es = dynamic_cast<EmptySquare*>(s);
          // Touching enemies is not allowed
          if(es->getEnemy() != 0) {
              takeDamage();
              curLvl->removeEnemy(es->getEnemy());
              es->setEnemy(0);
          }
          if(es->getPowerup() != 0) {
              es->getPowerup()->get(this);
              delete es->getPowerup();
              es->setPowerup(0);
          }
          // Make the move
          curSquare->setPlayer(0);
          es->setPlayer(this);
          curSquare = es;
          facing = dir;
        }
    }
}
