#include "world/level.h"
#include "tools/fastrandom.h"
#include <stdio.h>
#include "tools/directions.h"
#include <iostream>
#include <vector>
#include <math.h>
#include <queue>
#include <map>
#include <limits>
#include <thread>
#include "game.h"
#include "entities/projectiles/playerprojectile.h"
#include "entities/projectiles/georgebullet.h"
#include "entities/projectiles/georgelaser.h"
#include "tools/distance.h"
#include "entities/powerups/hp.h"
#include "entities/powerups/fasterbullets.h"


Level::Level(){}

Level::Level(int w, int h, Game* g, int vd, int d) {
    game = g;
    width = w;
    height = h;
    doorx = width/2;
    doory = height/2;
    george = 0;
    viewDistance = (vd < 5) ? 5 : vd;
    depth = d;

    board = NULL;
}

Level::~Level() {
    if(george) delete george;

    for(auto &i : enemies) {
        delete i;
    }
    for(auto &i : projectiles) {
        delete i;
    }

    for(int i = 0; i < width; i++) {
        for(int j = 0; j < height; j++) {
            delete board[i][j];
        }
        delete[] board[i];
    }
    delete[] board;
}

void Level::setPlayer(Player* p) {
    player = p;
}

void Level::initPlayer() {
    EmptySquare* startSquare = dynamic_cast<EmptySquare*>(board[doorx][doory]);
    startSquare->setPlayer(player);
    player->setSquare(startSquare);
}

void Level::initPlayer(Direction d) {
    // If door was right, now we start left and vice versa
    int startx = 0, starty = 0;
    switch(d) {
        case DIR_LEFT: starty = doory; startx = width-2; break;
        case DIR_RIGHT: starty = doory; startx = 1; break;
        case DIR_UP: starty = height-2; startx = doorx; break;
        case DIR_DOWN: starty = 1; startx = doorx; break;
        default: break;
    }
    EmptySquare* startSquare = dynamic_cast<EmptySquare*>(board[startx][starty]);
    startSquare->setPlayer(player);
    player->setSquare(startSquare);
}

std::set<Projectile*>* Level::getProjectiles() {
    return &projectiles;
}

void Level::newProjectile(Projectile* p) {
    projectiles.insert(p);
}

void Level::removeProjectile(Projectile* p) {
    delete *projectiles.find(p);
    projectiles.erase(projectiles.find(p));
}

Square* Level::getSquareDir(Square* s, Direction dir) {
    int y = s->getY();
    int x = s->getX();
    switch (dir) {
        case DIR_UP: y--; break; case DIR_LEFT: x--; break;
        case DIR_DOWN: y++; break; case DIR_RIGHT: x++; break;
    }
    if(x < 0 || x > width-1 || y < 0 || y > height-1) {
        return NULL;
    }
    return board[x][y];
}

void Level::removeEnemy(Enemy* e) {
    delete *enemies.find(e);
    enemies.erase(enemies.find(e));
}

void Level::updateEnemies() {
    std::thread* enemyThreads = new std::thread[enemies.size()];
    int idx = 0;
    for(auto &i : enemies) {
        enemyThreads[idx] = std::thread(&Enemy::decideMove, i);
        enemyThreads[idx++].join();
    }
    delete[] enemyThreads;
    std::vector<Enemy*> toDelete;
    for(auto &i: enemies) {
        if(i->act() == -1) {
            toDelete.push_back(i);
        }
    }
    for(auto &i: toDelete) {
        i->getSquare()->setEnemy(0);
        removeEnemy(i);
    }
}

void Level::updateProjectiles() {
    std::vector<Projectile*> toDelete;
    for(auto &i : projectiles) {
        if(i->move() == -1) {
            toDelete.push_back(i);
        }
    }
    for(auto &i: toDelete) {
        i->getSquare()->setProjectile(0);
        removeProjectile(i);
    }
}

void Level::updateGeorge() {
  if(george != 0) {
    george->act();
  }
}

void Level::setNeighbour(Direction dir, Level* l)  {
    neighbours[dir] = l;
}


void Level::signalGameOver(bool won) {
    game->over(won);
}

void Level::switchLevel(Direction dir) {
    std::cout << std::endl;

    if(!neighbours.count(dir)) {
        neighbours[dir] = newLevel(dir);
    }

    // Switch to this new level
    neighbours[dir]->initPlayer(dir);
    game->setLevel(neighbours[dir]);
    player->setLevel(neighbours[dir]);
}

//wrapper om oude code werkend te houden
//TODO function call vervangen door nieuwe
Level* Level::newLevel(Direction dir) {
    return game->newLevel(this, width, height, dir, viewDistance-SIGHT_DETERIORATION);
}

void Level::setGeorge() {
    int y = 3;
    int x = width/2 - 1;
    EmptySquare* georgeStart = dynamic_cast<EmptySquare*>(board[x][y]);
    george = new George(this, georgeStart, FPS);
}

void Level::hurtGeorge() {
  if(george->takehit()) {
    signalGameOver(true);
  }
}

void Level::toStartLevel() {
    std::cout << "to start level" << std::endl;

    Level* startLvl = game->getStartLevel();
    game->setLevel(startLvl);
    startLvl->initPlayer();
    player->setLevel(startLvl);
}

void Level::setRoom(Square*** b) {
    if(board != NULL) {
        for (int i = 0; i < width; i++)
            delete[] board[i];
    }

    board = b;
}

Player* Level::getPlayer() {
    return player;
}

void Level::spawnEnemy(Square* s) {
    EmptySquare* es = dynamic_cast<EmptySquare*>(s);
    Enemy* tmp = new Enemy(this, es);
    es->setEnemy(tmp);
}

void Level::spawnHeart(Square* s) {
    EmptySquare* es = dynamic_cast<EmptySquare*>(s);
    es->setPowerup(new Hp);
}

Square* Level::getSquare(int x, int y) {
    return board[x][y];
}

int Level::getWidth() const {
  return width;
}

int Level::getHeight() const {
  return height;
}

int Level::getViewDistance() const {
    return viewDistance;
}

int Level::getDepth() const {
    return depth;
}

void Level::addEnemy(Enemy* e) {
    enemies.insert(e);
}

bool Level::noEnemies() {
  return enemies.empty();
}

George* Level::getGeorge() {
  return george;
}
