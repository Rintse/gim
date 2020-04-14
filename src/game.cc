#include "game.h"
#include "kbhit.h"
#include <iostream>

//TODO: misschien niet last?
int lastKeyPressed() {
    std::string in;
    if (_kbhit()) {
        std::cin >> in;
        return in[in.length()-1];
    }
    else {
        return -1;
    }
}

ACTION getAction(char key) {
    switch (key) {
        case 'w': return MOVEUP;
        case 's': return MOVEDOWN;
        case 'd': return MOVERIGHT;
        case 'a': return MOVELEFT;
        case -1 : return NONE;
        case ' ': return SHOOT;
    }
}

Game::Game() {
    gameOver = false;
}

void Game::run() {
    while(!gameOver) {
        char lastKey = lastKeyPressed();
        ACTION act = getAction(lastKey);

    }
}
