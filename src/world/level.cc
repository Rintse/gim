#include "world/level.h"
#include "tools/fastrandom.h"
#include <stdio.h>
#include "tools/directions.h"
#include <iostream>
#include <vector>
#include "game.h"

Level::Level(){}

Level::Level(int w, int h, Game* g) {
    game = g;
    width = w;
    height = h;
    doorx = width/2;
    doory = height/2;

    board = new Square**[width];
    for(int i = 0; i < width; ++i) {
        board[i] = new Square*[height];
    }
}

Level::~Level() {
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
    Square* startSquare = board[doorx][doory];
    startSquare->setPlayer(player);
    player->setSquare(startSquare);
}

void Level::initPlayer(Direction d) {
    // If door was, right now we start left and vice versa
    int startx = d == DIR_LEFT ? width-1 : 0;
    Square* startSquare = board[startx][doory];
    startSquare->setPlayer(player);
    player->setSquare(startSquare);
}


void Level::newProjectile(Square* start, Direction dir) {
    Projectile* tmp = new Projectile(this, start, dir);
    start->setProjectile(tmp);
    projectiles.insert(tmp);
}

void Level::removeProjectile(Projectile* p) {
    projectiles.erase(projectiles.find(p));
    std::cout << "projectile deleted" << std::endl;
}

Square* Level::getSquareDir(Square* s, Direction dir) {
    int y = s->getY();
    int x = s->getX();
    switch (dir) {
        case DIR_UP: y--; break; case DIR_LEFT: x--; break;
        case DIR_DOWN: y++; break; case DIR_RIGHT: x++; break;
    }
    return board[x][y];
}

void Level::removeEnemy(Enemy* e) {
    enemies.erase(enemies.find(e));
}

void Level::updateEnemies() {

}

void Level::updateProjectiles() {
    std::vector<Projectile*> toDelete;
    for(auto &i : projectiles) {
        if(i->move() == -1) {
            toDelete.push_back(i);
        }
    }

    for(auto &i: toDelete) {
        i->getCurSquare()->setProjectile(0);
        projectiles.erase(projectiles.find(i));
    }
}


void Level::setNeighbour(Direction dir, Level* l)  {
    neighbours[dir] = l;
}


void Level::newLevel(Direction dir) {
    // Create new level and populate its board
    Level* tmp = new Level(width, height, game);
    tmp->randomGenerate();

    // Set all reference pointers
    tmp->setPlayer(player);
    player->setLevel(tmp);
    tmp->initPlayer(dir);
    tmp->setNeighbour(opposite_dir(dir), this);
    neighbours[dir] = tmp;

    // Switch to this new level
    game->setLevel(tmp);
}


void Level::generateStartRoom() {
    for(int i = 0; i < width; i++) {
        for(int j = 0; j < height; j++) {
            // Edges
            if(i == 0 || j == 0 || i == width-1 || j == height-1) {
                if( (j == 0 && i == doorx) ||
                ((i == 0 || i == width-1) && j == doory)) {
                    Direction dir = i==0 ? DIR_LEFT : DIR_RIGHT;
                    board[i][j] = new DoorSquare(i,j,dir);
                }
                else {
                    board[i][j] = new WallSquare(i,j);
                }
            }
            else {
                board[i][j] = new EmptySquare(i,j);
            }
        }
    }
}

void Level::randomGenerate() {
    for(int i = 0; i < width; i++) {
        for(int j = 0; j < height; j++) {
            if((i == 0 || i == width-1) && j == doory) {
                Direction dir = i==0 ? DIR_LEFT : DIR_RIGHT;
                board[i][j] = new DoorSquare(i,j,dir);
                continue;
            }

            int rand = randgen.getLong() % 5;
            if(rand == 0) {
                board[i][j] = new WallSquare(i,j);
            }
            else {
                board[i][j] = new EmptySquare(i,j);
            }
        }
    }
}

void Level::print() {
    char* str = new char[width*height+height+1];
    int strIdx = 0;

    for(int j = 0; j < height; j++) {
        for(int i = 0; i < width; i++) {
            if(board[i][j]->getPlayer() != 0) {
                str[strIdx++] = player->token();
            }
            else if(board[i][j]->getEnemy() != 0) {
                str[strIdx++] = 'x';
            }
            else if(board[i][j]->getProjectile() != 0) {
                str[strIdx++] = 'o';
            }
            else {
                str[strIdx++] = board[i][j]->token();
            }
        }
        str[strIdx++] = '\n';
    }

    // Add nullbyte to terminate and print with fprint
    str[strIdx] = '\0';
    printf("%s\n", str);

    delete[] str;
}

void Level::draw() {

}

inline Square* Level::getSquare(int x, int y) {
    return board[x][y];
}
