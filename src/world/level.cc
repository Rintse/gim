#include "world/level.h"
#include "fastrandom.h"
#include <stdio.h>

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

void Level::randomGenerate() {
    for(int i = 0; i < width; i++) {
        for(int j = 0; j < height; j++) {
            int rand = randgen.getLong() % 5;
            if(rand == 0) {
                board[i][j] = new WallSquare;
            }
            else {
                board[i][j] = new EmptySquare;
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

Square* Level::getSquare(int x, int y) {
    return board[x][y];
}
