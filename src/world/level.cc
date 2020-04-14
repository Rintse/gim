#include "world/level.h"
#include "fastrandom.h"

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

Square* Level::getSquare(int x, int y) {
    return board[x][y];
}
