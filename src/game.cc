#include "game.h"
#include <iostream>
#include <chrono>
#include <thread>
#include "tools/actions.h"
#include "tools/key_input.h"


void sleep_remaining(std::chrono::time_point<std::chrono::high_resolution_clock> t1) {
    auto updateT = std::chrono::duration_cast<std::chrono::milliseconds>
                        (std::chrono::high_resolution_clock::now() - t1);
    int millisLeft = FRAMETIME-updateT.count();
    if(millisLeft > 0)
        std::this_thread::sleep_for(std::chrono::milliseconds(millisLeft));
}


Game::Game() : gfx(GFX(this)){
    gameOver = false;
}

Game::~Game(){
    delete player;
    delete kh;
    for(auto & i : levels) {
        delete i;
    }
}

void Game::addLevel(Level* l) {
    levels.push_back(l);
}

void Game::setLevel(Level* l) {
    curLvl = l;
}

Level* Game::getLevel() {
    return curLvl;
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
    levels.push_back(curLvl);

    gfx.init();
    kh = new KeyHandler();
}

void Game::run() {
    while(!gameOver) {
        auto t1 = std::chrono::high_resolution_clock::now();

        // Update all entities
        Input in = kh->getInput();
        if(in.act == GAME_PAUSE) break;
        player->act(in);
        curLvl->updateProjectiles();
        curLvl->updateEnemies();

        // Draw to the screen
        gfx.drawGame();
        sleep_remaining(t1);
    }
}
