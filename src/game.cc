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
    gameOver = paused = false;
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

void Game::over() {
    gameOver = true;
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

int Game::init() {
    int err = 0;
    if(gfx.checkScreenSize() != 0) {
        err = -1;
    }

    curLvl = new Level(LVL_WIDTH, LVL_HEIGHT, this);
    player = new Player(curLvl);
    curLvl->setPlayer(player);
    curLvl->generateStartRoom();
    curLvl->initPlayer();
    levels.push_back(curLvl);

    gfx.init();

    kh = new KeyHandler();
    return err;
}

void Game::run() {
    while(!gameOver) {
        auto t1 = std::chrono::high_resolution_clock::now();
        Input in = kh->getInput();
        if(in.act == GAME_PAUSE) {
            paused = !paused;
            continue;
        }
        else if(in.act == GAME_CLOSE) {
            if(paused) break;
        }

        if(paused) {
            gfx.drawPauseMenu();
        }
        else {
            // Update all entities
            curLvl->updateProjectiles();
            curLvl->updateEnemies();
            curLvl->updateGeorge();
            player->act(in);
            // Draw to the screen
            gfx.drawGame();
        }

        sleep_remaining(t1);
    }
}
