#include "game.h"
#include <iostream>
#include <chrono>
#include <thread>
#include "tools/actions.h"
#include "tools/user_input.h"


void sleep_remaining(std::chrono::time_point<std::chrono::high_resolution_clock> t1) {
    auto updateT = std::chrono::duration_cast<std::chrono::milliseconds>
                        (std::chrono::high_resolution_clock::now() - t1);
    int millisLeft = FRAMETIME-updateT.count();
    if(millisLeft > 0)
        std::this_thread::sleep_for(std::chrono::milliseconds(millisLeft));
}


Game::Game() {
    gameOver = false;
}

void Game::setLevel(Level* l) {
    curLvl = l;
}

FastRandom* Game::getRNG() {
    return &randgen;
}

void Game::init() {
    curLvl = new Level(LVL_WIDTH, LVL_HEIGHT, this);
    player = new Player(curLvl);
    curLvl->setPlayer(player);
    curLvl->generateStartRoom();
    curLvl->initPlayer();
    curLvl->createBossRoom();
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

        sleep_remaining(t1);
    }
}
