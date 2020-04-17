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
    // If door was right, now we start left and vice versa
    int startx, starty;
    switch(d) {
        case DIR_LEFT: starty = doory; startx = width-2; break;
        case DIR_RIGHT: starty = doory; startx = 1; break;
        case DIR_UP: starty = height-2; startx = doorx; break;
        case DIR_DOWN: starty = 1; startx = doorx; break;
        default: break;
    }
    Square* startSquare = board[startx][starty];
    startSquare->setPlayer(player);
    player->setSquare(startSquare);
}


void Level::newProjectile(Square* start, Direction dir) {
    Projectile* tmp = new PlayerProjectile(this, start, dir);
    start->setProjectile(tmp);
    projectiles.insert(tmp);
}

void Level::removeProjectile(Projectile* p) {
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
    enemies.erase(enemies.find(e));
}

void Level::updateEnemies() {
    std::vector<Enemy*> toDelete;
    for(auto &i: enemies) {
        if(i->act() == -1) {
            toDelete.push_back(i);
        }
    }

    for(auto &i: toDelete) {
        i->getCurSquare()->setEnemy(0);
        enemies.erase(enemies.find(i));
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
        i->getCurSquare()->setProjectile(0);
        projectiles.erase(projectiles.find(i));
    }
}


void Level::setNeighbour(Direction dir, Level* l)  {
    neighbours[dir] = l;
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


Level* Level::newLevel(Direction dir) {
    // Create new level and populate its board
    Level* tmp = new Level(width, height, game);
    tmp->generateRandomRoom();

    // Set all reference pointers
    tmp->setPlayer(player);
    tmp->setNeighbour(opposite_dir(dir), this);
    game->addLevel(tmp);

    return tmp;
}

void Level::createBossRoom() {
    Level* tmp = new Level(width, height, game);
    tmp->generateBossRoom();
    tmp->setNeighbour(DIR_DOWN, this);
    tmp->setPlayer(player);
    game->addLevel(tmp);
    neighbours[DIR_UP] = tmp;
}

void Level::generateBossRoom() {
    for(int i = 0; i < width; i++) {
        for(int j = 0; j < height; j++) {
            // Edges
            if(i == 0 || j == 0 || i == width-1 || j == height-1) {
                // Door on bottom
                if(j == height-1 && i == doorx) {
                    board[i][j] = new DoorSquare(i,j,DIR_DOWN);
                }
                else { // Walls around the entire thing
                    board[i][j] = new WallSquare(i,j);
                }
            }
            else {
                board[i][j] = new EmptySquare(i,j);
            }
        }
    }
}

void Level::generateStartRoom() {
    for(int i = 0; i < width; i++) {
        for(int j = 0; j < height; j++) {
            // Edges
            if(i == 0 || j == 0 || i == width-1 || j == height-1) {
                // Doors on top, left, right
                if( (j == 0 && i == doorx) ||
                ((i == 0 || i == width-1) && j == doory)) {
                    Direction dir;
                    if(i == 0) dir = DIR_LEFT;
                    else if(i == width-1) dir = DIR_RIGHT;
                    else dir = DIR_UP;
                    board[i][j] = new DoorSquare(i,j,dir);
                }
                else { // Walls around the entire thing
                    board[i][j] = new WallSquare(i,j);
                }
            }
            // Hallway
            else if((i < doorx-6 && j < doory-6) || (i > doorx+6 && j < doory-6) ||
                    (i < doorx-6 && j > doory+6) || (i > doorx+6 && j > doory+6)) {
                board[i][j] = new WallSquare(i,j);
            }
            else {
                board[i][j] = new EmptySquare(i,j);
            }
        }
    }
}

void Level::generateRandomRoom() {
    for(int i = 0; i < width; i++) {
        for(int j = 0; j < height; j++) {
            if(i == 0 || j == 0 || i == width-1 || j == height-1) {
                if((i == 0 || i == width-1) && j == doory) {
                    Direction dir = i==0 ? DIR_LEFT : DIR_RIGHT;
                    board[i][j] = new DoorSquare(i,j,dir);
                    continue;
                }
                else {
                    board[i][j] = new WallSquare(i,j);
                }
            }
            else {
                int rand = game->getRNG()->getLong() % 10;
                if(rand == 0) {
                    board[i][j] = new WallSquare(i,j);
                }
                else {
                    board[i][j] = new EmptySquare(i,j);
                }
            }
        }
    }
}

void Level::print() {
    char* str = new char[(width*height*3) + height + 1];
    int strIdx = 0;

    for(int j = 0; j < height; j++) {
        for(int i = 0; i < width; i++) {
            str[strIdx++] = ' ';
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
            str[strIdx++] = ' ';
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

Square* Level::getSquare(int x, int y) {
    return board[x][y];
}
