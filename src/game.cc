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


Game::Game() : gfx(GFX(this)), levelgen(LevelGenerator(LVL_WIDTH, LVL_HEIGHT)) {
    state = STATE_START;
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

Level* Game::newLevel(Level* neighbour, int width, int height, Direction dir, int viewDistance) {

    Level* tmp = new Level(width, height, this, viewDistance, neighbour->getDepth()+1);
    levelgen.setLevel(tmp);

    Square*** newBoard = levelgen.cpeRoom(DIR_LEFT, height/2, DIR_RIGHT, height/2, tmp->getDepth());

    tmp->setRoom(newBoard);
    tmp->setPlayer(player);
    tmp->setNeighbour(opposite_dir(dir), neighbour);

    levels.push_back(tmp);

    return tmp;
}

void Game::over(bool won) {
    if(won) state = STATE_WON;
    else state = STATE_LOST;
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
    //START ROOM
    curLvl = new Level(LVL_WIDTH, LVL_HEIGHT, this, LVL_WIDTH);
    startLvl = curLvl;

    levelgen.setLevel(curLvl);

    Square*** start = levelgen.startRoom(LVL_WIDTH, LVL_HEIGHT, LVL_HEIGHT/2, LVL_WIDTH/2);

    player = new Player(curLvl);
    curLvl->setPlayer(player);
    curLvl->setRoom(start);
    curLvl->initPlayer();

    //BOSS ROOM
    Level* bossLvl = new Level(LVL_WIDTH, LVL_HEIGHT, this, LVL_WIDTH);

    levelgen.setLevel(bossLvl);
    Square*** boss = levelgen.bossRoom(LVL_WIDTH, LVL_HEIGHT, {LVL_WIDTH/2, LVL_HEIGHT-1} );

    bossLvl->setRoom(boss);
    bossLvl->setGeorge();
    bossLvl->setNeighbour(DIR_DOWN, curLvl);
    bossLvl->setPlayer(player);

    //Set Levels
    curLvl->setNeighbour(DIR_UP, bossLvl);
    addLevel(bossLvl);
    addLevel(curLvl);

    gfx.init();

    kh = new KeyHandler();
    return err;
}


void Game::interfaceInputs(Input in) {
    // Pause and unpause
    if(in.act == GAME_PAUSE) {
        if(state == STATE_PAUSED) state = STATE_RUN;
        else if(state == STATE_RUN) state = STATE_PAUSED;
    }

    else if(in.act == GAME_CLOSE) {
        // Close the game
        if(state == STATE_PAUSED || state >= STATE_WON) state = STATE_CLOSED;
        // Start the game
        else if(state == STATE_START) state = STATE_RUN;
    }
}


void Game::run() {
    // Main game loop
    while(state != STATE_CLOSED) {
        auto t1 = std::chrono::high_resolution_clock::now();
        Input in = kh->getInput();

        // Handle pauses, closes, etc.
        interfaceInputs(in);

        if(state == STATE_PAUSED) gfx.drawPauseMenu();
        else if(state >= STATE_WON) gfx.drawEndMenu(state == STATE_WON);
        else if(state == STATE_START) gfx.drawStartMenu();
        else if(state == STATE_CLOSED) continue;
        else { // state == STATE_RUN
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

Level* Game::getStartLevel() {
  return startLvl;
}
