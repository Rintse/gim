#include "world/level.h"
#include "fastrandom.h"
#include <stdio.h>
#include "directions.h"

Level::Level(){}

Level::Level(int w, int h) {
    width = w;
    height = h;

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

Square* Level::getSquareDir(Square* s, Direction dir) {
    int y = s->getY();
    int x = s->getX();
    switch (dir) {
        case DIR_UP: y++; break; case DIR_LEFT: x++; break;
        case DIR_DOWN: y--; break; case DIR_RIGHT: x--; break;
    }
    return board[x][y];
}

void Level::killEnemy(Enemy* e) {
    enemies.erase(enemies.find(e));
}

void Level::updateEnemies() {

}

void Level::updateProjectiles() {

}

void Level::randomGenerate() {
    for(int i = 0; i < width; i++) {
        for(int j = 0; j < height; j++) {
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
    char* str = new char[width*height+1];
    int strIdx = 0;

    for(int i = 0; i < width; i++) {
        for(int j = 0; j < height; j++) {
            str[strIdx++] = board[i][j]->token();
        }
    }

    // Add nullbyte to terminate and print with fprint
    str[strIdx] = '\0';
    printf("%s", str);

    delete[] str;
}

void Level::draw() {

}

inline Square* Level::getSquare(int x, int y) {
    return board[x][y];
}
