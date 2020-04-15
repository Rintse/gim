#include "game.h"
#include "kbhit.h"
#include <iostream>
#include <chrono>
#include <thread>
#include "actions.h"

//TODO: misschien niet last?
int lastKeyPressed() {
    char c;
    int inbuff = _kbhit();
    // If characters were pressed
    if(inbuff != 0) {
        // Get the last one
        for(int i = 0; i < inbuff; i++) {
            std::cin.get(c);
        }
        return c;
    }
    else {
        return -1;
    }
}

Action getAction(int key) {
    switch (key) {
        case 'w': return ACTION_MOVEUP;
        case 's': return ACTION_MOVEDOWN;
        case 'd': return ACTION_MOVERIGHT;
        case 'a': return ACTION_MOVELEFT;
        case ' ': return ACTION_SHOOT;
        default: case -1 : return ACTION_NONE;
    }
}

Game::Game() {
    gameOver = false;
}

void Game::init() {
    curLvl = new Level(LVL_WIDTH, LVL_HEIGHT);
    player = new Player(curLvl);
    curLvl->setPlayer(player);
    curLvl->generateStartRoom();
    curLvl->initPlayer();
}

void Game::run() {
    while(!gameOver) {
        auto t1 = std::chrono::high_resolution_clock::now();

        char lastKey = lastKeyPressed();
        Action action = getAction(lastKey);

        // Update all entities
        player->act(action);
        curLvl->updateProjectiles();
        curLvl->updateEnemies();

        // Draw to the screen
        curLvl->print();

        auto updateT = std::chrono::duration_cast<std::chrono::milliseconds>
                            (std::chrono::high_resolution_clock::now() - t1);
        int millisLeft = FRAMETIME-updateT.count();
        if(millisLeft > 0)
            std::this_thread::sleep_for(std::chrono::milliseconds(millisLeft));
    }
}
