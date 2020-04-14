#include "player.h"

Player::Player(World w) {
    world = w;
}

int Player::move(int direction) {
    Square s;
    switch(direction) {
        case 0: //left
            //s = curLvl.getSquare(0);
            break;
        case 1: //up
            break;
        case 2: //down
            break;
        case 3: //right
            break;
    }

    return 0;
}
